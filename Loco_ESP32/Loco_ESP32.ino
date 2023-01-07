//==============================================================================================

//==============================================================================================

#include <esp_now.h>
#include <WiFi.h>

#include <pwmWrite.h>    //https://github.com/Dlloydev/ESP32-ESP32S2-AnalogWrite
#include <AceRoutine.h>  //https://github.com/bxparks/AceRoutine
using namespace ace_routine;

#include "defaultPins.h"
#include "defaultLoco.h"

//==============================================================================================
#define AuthName "Dragon";
#define LocoID 2917
#define AuthCode 0000

//==============================================================================================
#define ESPNOW_DEBUG      //  View ESPnow and Received Data
//#define MOTOR_DEBUG       // Debug info of DC motor driver
//#define ACCEL_DEBUG       // Visualize Acceleration with Serial Plotter

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

Pwm pwm = Pwm();

void setup() {

#ifdef ESPNOW_DEBUG || MOTOR_DEBUG || ACCEL_DEBUG
  Serial.begin(115200);
  Serial.println("Dragon Railway Locomotive");
#endif
  WiFi.mode(WIFI_STA);
  InitESPNow();
  esp_now_register_recv_cb(OnDataRecv);  //Reciever CallBack function

  MotorSetup();

  CoroutineScheduler::setup();
}

void loop() {
  CoroutineScheduler::loop();
}
