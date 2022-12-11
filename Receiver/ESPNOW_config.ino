
typedef struct rc_struct {
  short loconumber;
  short ch1;
  short ch2;
  short ch3;
  short ch4;
  short ch5;
  short ch6;
} rc_struct;
rc_struct rcData;

short channel_1 = ppmMid;  // Throttle
short channel_2 = ppmMid;  // Direction
short channel_3 = ppmMid;  // Light
short channel_4 = ppmMid;  // Coupler
short channel_5 = ppmMid;  // extra 1
short channel_6 = ppmMid;  // extra 2

#define WIFICHANNEL 1

//==============================================================================================
void OnDataRecv(const uint8_t *mac, const uint8_t *receivedData, int len) {
  memcpy(&rcData, receivedData, sizeof(rcData));
  // Channel values are assigned only for the assigned LocoNumber only
  if (rcData.loconumber = LocoNumber) {
    channel_1 = rcData.ch1;
    channel_2 = rcData.ch2;
    channel_3 = rcData.ch3;
    channel_4 = rcData.ch4;
    channel_5 = rcData.ch5;
    channel_6 = rcData.ch6;
  }
}

void InitESPNow() {
  WiFi.disconnect();
  if (esp_now_init() == ESP_OK) {
    Serial.println("ESPNow Init Success");
  } else {
    Serial.println("ESPNow Init Failed");
    ESP.restart();
  }
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
