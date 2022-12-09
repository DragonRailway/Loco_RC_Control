void InitESPNow() {
  WiFi.disconnect();
  if (esp_now_init() == ESP_OK) { Serial.println("ESPNow Init Success");  }
  else { Serial.println("ESPNow Init Failed"); ESP.restart();  }
}

void manageLocos() {
  if (LocoCount > 0) {
    for (int i = 0; i < LocoCount; i++) {
      Serial.print("Processing: ");
      for (int ii = 0; ii < 6; ++ii ) {
        Serial.print((uint8_t) devices[i].peer_addr[ii], HEX);
        if (ii != 5) Serial.print(":");
      }
      Serial.print(" Status: ");
      
      bool exists = esp_now_is_peer_exist(devices[i].peer_addr); // check if the Loco exists
      if (exists) {        
        Serial.println("Loco Already Paired"); // Device already paired.
      } else {        
        esp_err_t addStatus = esp_now_add_peer(&devices[i]); // Device not paired, Pairing...
        if (addStatus == ESP_OK) {          
          Serial.println("Pair success"); // Pairing successful
        } else if (addStatus == ESP_ERR_ESPNOW_NOT_INIT) {          
          Serial.println("ESPNOW Not Init");
        } else if (addStatus == ESP_ERR_ESPNOW_ARG) {
          Serial.println("Add Peer - Invalid Argument");
        } else if (addStatus == ESP_ERR_ESPNOW_FULL) {
          Serial.println("Peer list full");
        } else if (addStatus == ESP_ERR_ESPNOW_NO_MEM) {
          Serial.println("Out of memory");
        } else if (addStatus == ESP_ERR_ESPNOW_EXIST) {
          Serial.println("Peer Exists");
        } else {
          Serial.println("Not sure what happened");
        }
      }
    }
  } else {    
    Serial.println("No Locos found to connect");
  }
}

void FindNearbyLocos() {
  int8_t scanResults = WiFi.scanNetworks();  
  memset(devices, 0, sizeof(devices)); //reset devices
  LocoCount = 0;
  Serial.println("");
  if (scanResults == 0) {
    Serial.println("No Locos in AP Mode found");
  } else {
    Serial.print("Found "); Serial.print(scanResults); Serial.println(" Devices ");
    for (int i = 0; i < scanResults; ++i) {      
      String SSID = WiFi.SSID(i);
      int32_t RSSI = WiFi.RSSI(i);
      String BSSIDstr = WiFi.BSSIDstr(i);
      if (PRINTSCANRESULTS) { // Show SSID and RSSI for devices found
        Serial.print(i + 1); Serial.print(": "); Serial.print(SSID); Serial.print(" ["); Serial.print(BSSIDstr); Serial.print("]"); Serial.print(" ("); Serial.print(RSSI); Serial.print(")"); Serial.println("");
      }      
      if (SSID.indexOf("DragonControlSystem") == 0) { // Find devices starting with "DragonControlSystem"
        Serial.print(i + 1); Serial.print(": "); Serial.print(SSID); Serial.print(" ["); Serial.print(BSSIDstr); Serial.print("]"); Serial.print(" ("); Serial.print(RSSI); Serial.print(")"); Serial.println("");
        int mac[6]; // Get Mac Address of the Device

        if ( 6 == sscanf(BSSIDstr.c_str(), "%x:%x:%x:%x:%x:%x",  &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5] ) ) {
          for (int ii = 0; ii < 6; ++ii ) {
            devices[LocoCount].peer_addr[ii] = (uint8_t) mac[ii];
        }  }
        devices[LocoCount].channel = CHANNEL; // pick a channel
        devices[LocoCount].encrypt = 0; // no encryption
        LocoCount++;
      } } }
  if (LocoCount > 0) {  Serial.print(LocoCount); Serial.println(" Loco found");
  } else { Serial.println("No Locos Found, checking again."); 
  }  WiFi.scanDelete();
  }
  