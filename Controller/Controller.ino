#include <esp_now.h>
#include <WiFi.h>

typedef struct rc_struct {
  short loco_number;
  short ch1;
  short ch2;
  short ch3;
  short ch4;
  short ch5;
  short ch6;
} rc_struct;

esp_now_peer_info_t devices[LOCONUMBER] = {};
int LocoCount = 0;

#define LOCONUMBER 8
#define CHANNEL 8
#define PRINTSCANRESULTS 0

uint8_t *peer_addr;

void InitESPNow();
void FindNearbyLocos();
void manageLocos();

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  Serial.println("Dragon_Locomotive_Contoller");
  Serial.print("STA MAC: ");
  Serial.println(WiFi.macAddress());
  InitESPNow();
  esp_now_register_send_cb(OnDataSent);
}

void loop() {
  FindNearbyLocos();
  if (LocoCount > 0) {
    manageLocos();
    transmitData();
  } else {
  }
}