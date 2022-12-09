
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
//========================================================================================================

int LocoCount = 0;

void InitESPNow();
void FindNearbyLocos();
void manageLocos();

void setup() {
  WiFi.mode(WIFI_STA);
  InitESPNow();
  esp_now_register_send_cb(OnDataSent);
  FindNearbyLocos();
#ifdef ESPNOW_DEBUG  
  Serial.begin(115200);
  Serial.println("Dragon_Locomotive_Contoller");
  Serial.print("STA MAC: ");
  Serial.println(WiFi.macAddress());
#endif
}

void loop() {
  if (LocoCount > 0) {
    for (int i = 0; i <= 3; i++) {  // Loop repeats 4 times for 4 Locomotives
      processinputs();
      manageLocos();
      transmitData();
    }
  } else {
    FindNearbyLocos();
  }
}