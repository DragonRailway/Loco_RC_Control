
uint8_t *peer_addr;

void transmitData() {
  for (int i = 0; i < connectedLoco; i++) {
    const uint8_t *peer_addr = devices[i].peer_addr;
  }
  esp_err_t result = esp_now_send(peer_addr, (uint8_t *)&rcData, sizeof(rc_struct));

  //#ifdef ESPNOW_DEBUG
  Serial.print("Send Status: ");
  if (result == ESP_OK) {
    Serial.println("Success");
  } else if (result == ESP_ERR_ESPNOW_NOT_INIT) {
    // How did we get so far!!
    Serial.println("ESPNOW not Init.");
  } else if (result == ESP_ERR_ESPNOW_ARG) {
    Serial.println("Invalid Argument");
  } else if (result == ESP_ERR_ESPNOW_INTERNAL) {
    Serial.println("Internal Error");
  } else if (result == ESP_ERR_ESPNOW_NO_MEM) {
    Serial.println("ESP_ERR_ESPNOW_NO_MEM");
  } else if (result == ESP_ERR_ESPNOW_NOT_FOUND) {
    Serial.println("Peer not found.");
  } else {
    Serial.println("Not sure what happened");
  }
  //#endif
}

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
#ifdef ESPNOW_DEBUG
  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print("Transmitted to: ");
  Serial.println(macStr);
  Serial.print("Transmit status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Failed");
#endif
}
