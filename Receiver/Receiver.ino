
//==============================================================================================
#include <esp_now.h>
#include <WiFi.h>

#include "Loco_Config.h"
//==============================================================================================
// This Code must match the controllers's PairCode
char PAIRCODE[] = "DragonControlSystem";

// Set the locomotive number
#define LocomotiveNumber 2

//==============================================================================================
// SET PINS

//==============================================================================================
// Debug options can be commented out if not required
#define ESPNOW_DEBUG
//==============================================================================================
void InitESPNow();
void configDeviceAP();

void setup() {
  WiFi.mode(WIFI_AP);
  configDeviceAP();
  InitESPNow();
  esp_now_register_recv_cb(OnDataRecv);
#ifdef ESPNOW_DEBUG
  Serial.begin(115200);
  Serial.println("Dragon_Locomotive_Receiver");
  Serial.print("Loco MAC: ");
  Serial.println(WiFi.softAPmacAddress());
#endif
}

void loop() {
}
