
//==============================================================================================

//==============================================================================================

#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>  //  Wire.h for I2C OLED Display

//    Install
#include <Toggle.h>          //https://github.com/Dlloydev/Toggle
#include <U8g2lib.h>         //https:github.com/olikraus/u8g2
#include <PrintCharArray.h>  //https://github.com/RobTillaart/PrintCharArray
#include <AceRoutine.h>      //https://github.com/bxparks/AceRoutine
using namespace ace_routine;
#include "EncoderTool.h"  //https://github.com/luni64/EncoderTool
using namespace EncoderTool;

#include "defaultPins.h"
//==============================================================================================

#define AuthName "Dragon"
#define LocoID 4444
#define AuthCode 0000

U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);
//U8G2_SSD1306_128X64_ALT0_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);   // same as the NONAME variant, but may solve the "every 2nd line skipped" problem
//U8G2_SSD1306_128X64_NONAME_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* reset=*/ 8);
//U8G2_SSD1306_128X64_NONAME_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // All Boards without Reset of the Display
//U8G2_SSD1306_128X64_NONAME_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ 16, /* data=*/ 17, /* reset=*/ U8X8_PIN_NONE);   // ESP32 Thing, pure SW emulated I2C
//U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 22, /* data=*/ 21);   // ESP32 Thing, HW I2C with pin remapping

//==============================================================================================

//#define ESPNOW_DEBUG
#define INPUT_DEBUG
#define OLED_DEBUG
//==============================================================================================
uint8_t broadcastAddress[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };  // Broadcast mode

struct DataPack {
  char* NAME = AuthName;
  uint16_t ID = LocoID;
  uint16_t AUTH = AuthCode;
  uint8_t STATE = 1;
  int8_t THROTTLE = 0;
  int8_t DIRECTION = 0;
  int8_t LEFT = 0;
  int8_t RIGHT = 0;
  int8_t UP = 0;
  int8_t DOWN = 0;
  int8_t LIGHT = 0;
  int8_t HORN = 0;
  int8_t COUPLER = 0;
  int8_t EXTRA = 0;
};
DataPack rcdata;
//==============================================================================================

void setup() {

#ifdef ESPNOW_DEBUG || INPUT_DEBUG || OLED_DEBUG
  Serial.begin(115200);
  Serial.println("Dragon Loco Remote");
#endif

  WiFi.mode(WIFI_STA);
  InitESPNow();
  esp_now_register_send_cb(OnDataSent);

  OledSetup();
  SetupButtons();
  CoroutineScheduler::setup();
}
//==============================================================================================

void loop() {

  CoroutineScheduler::loop();
}
