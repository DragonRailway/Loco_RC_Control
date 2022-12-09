void InitESPNow() {
  WiFi.disconnect();
  if (esp_now_init() == ESP_OK) { Serial.println("ESPNow Init Success");  }
  else { Serial.println("ESPNow Init Failed"); ESP.restart();  }
}

void configDeviceAP() {
  String Prefix = "DragonControlSystem:";
  String Mac = WiFi.macAddress();
  String SSID = Prefix + Mac;
  String Password = "123456789";
  bool result = WiFi.softAP(SSID.c_str(), Password.c_str(), CHANNEL, 0);
  if (!result) {
    Serial.println("Loco AP Config failed.");
  } else {
    Serial.println("Loco Config Success. Broadcasting with AP: " + String(SSID));
  }
}