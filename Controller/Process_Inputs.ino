
short channel_1[] = { 0, 0, 0, 0 };  // Throttle Potentiometer
short channel_2[] = { 0, 0, 0, 0 };  // Direction Two state Switch
short channel_3[] = { 0, 0, 0, 0 };  // Light Switch
short channel_4[] = { 0, 0, 0, 0 };  // Momentary switch
short channel_5[] = { 0, 0, 0, 0 };  // extra 1
short channel_6[] = { 0, 0, 0, 0 };  // extra 2

void processinputs() {

  rcData.loconumber = LocoNumber;

  channel_1[LocoNumber] = analogRead(POT[LocoNumber]);
  channel_1[LocoNumber] = map(channel_1[LocoNumber], 0, 4095, ppmMin, ppmMax);
  rcData.ch1 = constrain(channel_1[LocoNumber], ppmMin, ppmMax);

  channel_2[LocoNumber] = digitalRead(DIR[LocoNumber]);
  channel_2[LocoNumber] = map(channel_2[LocoNumber], 0, 1, ppmMin, ppmMax);
  rcData.ch2 = constrain(channel_2[LocoNumber], ppmMin, ppmMax);

  channel_3[LocoNumber] = digitalRead(LIGHT[LocoNumber]);
  channel_3[LocoNumber] = map(channel_3[LocoNumber], 0, 1, ppmMin, ppmMax);
  rcData.ch3 = constrain(channel_3[LocoNumber], ppmMin, ppmMax);

  channel_4[LocoNumber] = digitalRead(MOMENTARY[LocoNumber]);
  channel_4[LocoNumber] = map(channel_4[LocoNumber], 0, 1, ppmMin, ppmMax);
  rcData.ch3 = constrain(channel_4[LocoNumber], ppmMin, ppmMax);

  channel_5[LocoNumber] = ppmMid;
  rcData.ch5 = channel_5[LocoNumber];

  channel_6[LocoNumber] = ppmMid;
  rcData.ch6 = channel_6[LocoNumber];

#ifdef CHANNEL_DEBUG
  Serial.print("Loco Number :");
  Serial.println(rcData.loconumber);
  Serial.print("Channel_1   :");
  Serial.println(rcData.ch1);
  Serial.print("Channel_2   :");
  Serial.println(rcData.ch2);
  Serial.print("Channel_3   :");
  Serial.println(rcData.ch3);
  Serial.print("Channel_4   :");
  Serial.println(rcData.ch4);
  Serial.print("Channel_5   :");
  Serial.println(rcData.ch5);
  Serial.print("Channel_6   :");
  Serial.println(rcData.ch6);
#endif
}