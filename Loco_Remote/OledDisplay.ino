//==============================================================================================
//#define OLED_DEBUG

byte OledAddress = 0x3C;  //  SD1306 display address is 0x3C or 0x3D
PrintCharArray ps;

#define WIRE Wire

void OledSetup() {

  u8g2.begin();
  u8g2.clearBuffer();

#ifdef OLED_DEBUG
  Serial.println("\n Scanning for OLED display");
  byte error, address;
  int nDevices;
  nDevices = 0;
  for (address = 1; address < 127; address++) {
    WIRE.beginTransmission(address);
    error = WIRE.endTransmission();
    if (error == 0 && (address == 0x3C || address == 0x3D)) {
      Serial.print("OLED Display found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
      if (address != OledAddress) {
        OledAddress = address;
        Serial.print("Change OledAddress to 0x");
        Serial.print(address, HEX);
        Serial.println("  !!!");
      } else {
        Serial.println("OLED display connection Successful");
      }
      nDevices++;
    } else if (error == 0) {
      Serial.print("Unknown I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
      nDevices++;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0) Serial.println("No I2C devices not found");
#endif
  //----------------------------------------------------
}

//==============================================================================================

void OledDash() {
  char* ModelID = AuthName;
  uint8_t OledSpeed = EncVal * 2;
  OledSpeed = constrain(OledSpeed, 0, 200);
  ps.clear();
  ps.println(OledSpeed, 10);
  char* SpeedBuffer = ps.getBuffer();

  u8g2.firstPage();
  do {
    //    Display a frame on the border - for debugging only
    //u8g2.drawFrame(0, 0, 128, 64);

    //    Draw Speed down-left corner
    u8g2.setFont(u8g2_font_logisoso42_tn);
    uint8_t SpeedX = 128 - 24 - u8g2.getStrWidth(SpeedBuffer) / 2;
    u8g2.setDrawColor(1);
    u8g2.drawStr(SpeedX, 62, SpeedBuffer);

    //    Display Locomotive Model Number
    u8g2.setFont(u8g2_font_helvB14_tf);
    uint8_t ModelX = u8g2.getStrWidth(ModelID) + 4;
    u8g2.setDrawColor(1);
    u8g2.drawRBox(0, 0, ModelX, 18, 3);
    u8g2.setDrawColor(0);
    u8g2.drawStr(2, 16, ModelID);

  } while (u8g2.nextPage());
}

//==============================================================================================