//==============================================================================================

void transmitData() {
  esp_err_t SendStatus = esp_now_send(broadcastAddress, (uint8_t *)&rcdata, sizeof(rcdata));
#ifdef ESPNOW_DEBUG
  if (SendStatus == ESP_OK) {
    Serial.println("Send success");
  } else {
    Serial.println("Failed");
  }
#endif
}

void InitESPNow() {

  // Init ESP-NOW
  WiFi.disconnect();
  if (esp_now_init() != ESP_OK) {
    ESP.restart();
  }
#ifdef ESPNOW_DEBUG
  if (esp_now_init() == ESP_OK) {
    Serial.println("ESPNow Init Success");
  } else {
    Serial.println("ESPNow Init Failed");
  }
#endif
  // Register peer
  esp_now_peer_info_t peerInfo;
  memset(&peerInfo, 0, sizeof(peerInfo));
  for (int ii = 0; ii < 6; ++ii) {
    peerInfo.peer_addr[ii] = (uint8_t)broadcastAddress[ii];
  }
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

// Data send acknowledgement - not relevant for broadcast mode
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
#ifdef ESPNOW_DEBUG2
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
#endif
}