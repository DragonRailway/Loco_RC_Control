
//==============================================================================================

//==============================================================================================

#include <WiFi.h>
#include <Wire.h>  //  Wire.h for I2C OLED Display
#include <esp_now.h>
#include <Esp.h>  // for displaying memory information

//    Install the following libraries (available through Arduino IDE

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

#define ESPNOW_DEBUG
#define INPUT_DEBUG
#define OLED_DEBUG
#define CORE_DEBUG
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

int8_t State = 0;
int8_t Throttle = 0;
int8_t Direction = 0;
int8_t Left = 0;
int8_t Right = 0;
int8_t Up = 0;
int8_t Down = 0;
int8_t Light = 0;
int8_t Horn = 0;
int8_t Coupler = 0;
int8_t Extra = 0;

int8_t EncVal=0;
//==============================================================================================
TaskHandle_t Task1;
TaskHandle_t Task2;

void setup() {

#ifdef ESPNOW_DEBUG || INPUT_DEBUG || OLED_DEBUG
  Serial.begin(115200);
  Serial.println("\n  Dragon Loco Remote");
#endif

  WiFi.mode(WIFI_STA);
  InitESPNow();
  esp_now_register_send_cb(OnDataSent);

  SetupButtons();

  xTaskCreatePinnedToCore(
    Task2code, /* Task function. */
    "Task2",   /* name of task. */
    10000,     /* Stack size of task */
    NULL,      /* parameter of the task */
    1,         /* priority of the task */
    &Task2,    /* Task handle to keep track of created task */
    1);        /* pin task to core 1 */
  delay(10);
  xTaskCreatePinnedToCore(
    Task1code, /* Task function. */
    "Task1",   /* name of task. */
    10000,     /* Stack size of task */
    NULL,      /* parameter of the task */
    1,         /* priority of the task */
    &Task1,    /* Task handle to keep track of created task */
    0);        /* pin task to core 0 */
  delay(10);
}
//==============================================================================================
//    Remote Functions are running on Core 1

void Task2code(void* pvParameters) {
#if defined CORE_DEBUG
  Serial.print("OLED running on core ");
  Serial.println(xPortGetCoreID());
#endif

  for (;;) {
    CheckInputs();
    ReadEncoder();
  }
}
//==============================================================================================
//    OLED Display is running on Core 0

void Task1code(void* pvParameters) {
  Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID());

  OledSetup();

  for (;;) {
    OledDash();
  }
}

//==============================================================================================
void loop() {}
