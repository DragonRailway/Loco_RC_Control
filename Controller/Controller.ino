//==============================================================================================
#include <esp_now.h>
#include <WiFi.h>

#include "ConfigFile.h"
//==============================================================================================
// This Code must match the receiver's PairCode
char PAIRCODE[] = "DragonControlSystem";

int connectedLoco = 0;
int LocoNumber = 0;

struct rc_struct {
  short loconumber;
  short ch1;
  short ch2;
  short ch3;
  short ch4;
  short ch5;
  short ch6;
} rcData = { ppmMid, ppmMid, ppmMid, ppmMid, ppmMid, ppmMid };

void InitESPNow();
void FindNearbyLocos();
void manageLocos();
void processinputs();
void transmitData();

void setup() {
  WiFi.mode(WIFI_STA);
  InitESPNow();
  esp_now_register_send_cb(OnDataSent);
  FindNearbyLocos();

#ifdef ESPNOW_DEBUG || CHANNEL_DEBUG
  Serial.begin(115200);
  Serial.println("Dragon_Locomotive_Contoller");
  Serial.print("STA MAC: ");
  Serial.println(WiFi.macAddress());
#endif
}

void loop() {
  if (connectedLoco > 0) {
    for (int LoopNumber = 0; LoopNumber < ControlNumber; LoopNumber++) {
      LocoNumber = LoopNumber;
      processinputs();
      manageLocos();
      transmitData();
    }
  } else {
    FindNearbyLocos();
  }
  if (digitalRead(pairPIN) == HIGH) {
    FindNearbyLocos();
  }
}