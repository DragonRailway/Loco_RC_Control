
#include <esp_now.h>
#include <WiFi.h>
//========================================================================================================
// This Code must match the receiver's PairCode
char PAIRCODE[] = "DragonControlSystem";

//========================================================================================================
// SET PINS
//
// PIN ARRAY setup = { TRAIN-1, TRAIN-2, TRAIN-3, TRAIN-4 }

const byte POT[] = { 12, 14, 27, 13 };  // Potentiometer for Speed/Throttle

const byte DIR[] = { 12, 14, 27, 13 };  // Toggle switch for Direction

const byte LIGHT[] = { 12, 14, 27, 13 };  // Toggle switch for Headlight

const byte MOMENTARY[] = { 12, 14, 27, 13 };  // Momentary swtich

#define pairPIN 22   // Connected to a Momentary switch for pairing Locomotives during operation
#define statusLED 5  // Led to indicate when atleast one Locomotive is connected

//========================================================================================================
// Debug options can be commented out if not required
#define ESPNOW_DEBUG
#define CHANNEL_DEBUG
//========================================================================================================

// Number of Trains to be controlled
#define ControlNumber 4
// Data is sent in Pulse width similar to conventional RC systems
#define ppmMin 1000
#define ppmMid 1500
#define ppmMax 2000

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
    for (int LoopNumber = 0; LoopNumber < ControlNumber; LoopNumber++) {  // Loop repeats 4 times for 4 Locomotives
      LocoNumber = LoopNumber;
      processinputs();
      manageLocos();
      transmitData();
    }
  } else {
    FindNearbyLocos();
  } if (digitalRead(pairPIN)==HIGH) {
    FindNearbyLocos();
  }
}