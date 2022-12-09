
typedef struct rc_struct {
  short loco_number;
  short ch1;
  short ch2;
  short ch3;
  short ch4;
  short ch5;
  short ch6;
} rc_struct;

int channel[6];
#define WIFICHANNEL 1

void OnDataRecv(const uint8_t * mac, const uint8_t *data, int len) {
   
  rc_struct* outputdata =(rc_struct*) data;
  
  Serial.println(outputdata->loco_number);
  Serial.println(outputdata->ch1);
  Serial.println(outputdata->ch2);
  Serial.println(outputdata->ch3);
  Serial.println(outputdata->ch4);
  Serial.println(outputdata->ch5);
  Serial.println(outputdata->ch6);
Serial.println(rc_struct.loconumber);
}

void InitESPNow() {
  WiFi.disconnect();
  if (esp_now_init() == ESP_OK) { Serial.println("ESPNow Init Success");  }
  else { Serial.println("ESPNow Init Failed"); ESP.restart();  }
}

void configDeviceAP() {
  String Mac = WiFi.macAddress();
  String SSID = PAIRCODE + Mac;
  String Password = "123456789";
  bool result = WiFi.softAP(SSID.c_str(), Password.c_str(), WIFICHANNEL, 0);
  if (!result) {
    Serial.println("Loco AP Config failed.");
  } else {
    Serial.println("Loco Config Success. Broadcasting with AP: " + String(SSID));
  }
}

