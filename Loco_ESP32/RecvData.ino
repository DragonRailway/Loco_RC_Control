//==============================================================================================

struct DataPack {
  char* NAME = "Dragon";
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

uint32_t lastRecvTime = 0;

//==============================================================================================
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  if (len == 0) {
    return;
  }
  memcpy(&rcdata, incomingData, sizeof(rcdata));
  lastRecvTime = millis();

  ReadData();
}

void ReadData() {
  State = rcdata.STATE;
  Throttle = rcdata.THROTTLE;
  Direction = rcdata.DIRECTION;
  Left = rcdata.LEFT;
  Right = rcdata.RIGHT;
  Up = rcdata.UP;
  Down = rcdata.DOWN;
  Light = rcdata.LIGHT;
  Horn = rcdata.HORN;
  Coupler = rcdata.COUPLER;
  Extra = rcdata.EXTRA;

#ifdef ESPNOW_DEBUG
  Serial.print(rcdata.NAME);
  Serial.print(", ");
  Serial.print(rcdata.ID);
  Serial.print(", ");
  Serial.print(Throttle);
  Serial.print(", ");
  Serial.print(Direction);
  Serial.print(", ");
  Serial.print(Left);
  Serial.print(", ");
  Serial.print(Right);
  Serial.print(", ");
  Serial.print(Up);
  Serial.print(", ");
  Serial.print(Down);
  Serial.print(", ");
  Serial.print(Light);
  Serial.print(", ");
  Serial.print(Horn);
  Serial.print(", ");
  Serial.print(Coupler);
  Serial.print(", ");
  Serial.print(Extra);
  Serial.print(", ");
  Serial.print(State);
  Serial.print(",  PacketSize:");
  Serial.println(sizeof(rcdata));
#endif  
}
//==============================================================================================

void InitESPNow() {
  
  WiFi.disconnect();
  if (esp_now_init() != ESP_OK) {
    ESP.restart();
  }
#ifdef ESP_DEBUG
  if (esp_now_init() == ESP_OK) {
    Serial.println("ESPNow Init Success");
  } else {
    Serial.println("ESPNow Init Failed");    // or Simply Restart
  }
#endif
}