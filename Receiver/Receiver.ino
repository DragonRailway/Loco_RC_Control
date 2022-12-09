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

#define CHANNEL 1

void setup() {
  Serial.begin(115200);
  Serial.println("Dragon_Locomotive_Receiver");
  WiFi.mode(WIFI_AP);
  configDeviceAP();
  Serial.print("Loco MAC: "); Serial.println(WiFi.softAPmacAddress());
  InitESPNow();
  esp_now_register_recv_cb(OnDataRecv);
}

void OnDataRecv(const uint8_t * mac, const uint8_t *data, int len) {
   
  rc_struct* outputdata =(rc_struct*) data;
   
  Serial.println(outputdata->loco_number);
  Serial.println(outputdata->ch1);
  Serial.println(outputdata->ch2);
  Serial.println(outputdata->ch3);
  Serial.println(outputdata->ch4);
  Serial.println(outputdata->ch5);
  Serial.println(outputdata->ch6);
 
}

void loop() {
  // Todo
}
