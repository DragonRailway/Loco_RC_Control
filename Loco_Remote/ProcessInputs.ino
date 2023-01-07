//==============================================================================================

int8_t State = 0;
int8_t Throttle = 0;
int8_t Direction = 0;
int8_t Left = 0;
int8_t Right = 0;
int8_t Up = 0;
int8_t Down = 0;
int8_t Light = 0;
int8_t Horn = 0;
int8_t Coupler = 0;
int8_t Extra = 0;
//==============================================================================================

Toggle EncButton(EncSW);
Toggle LeftButton(LeftBtn);
Toggle RightButton(RightBtn);
Toggle UpButton(UpBtn);
Toggle DownButton(DownBtn);
Toggle LightButton(LightBtn);
Toggle HornButton(HornBtn);
Toggle CouplerButton(CouplerBtn);
Toggle ExtraButton(ExtraBtn);

PolledEncoder enc;

void SetupButtons() {
  pinMode(UpLed, OUTPUT);
  pinMode(DownLed, OUTPUT);
  pinMode(LightLed, OUTPUT);
  pinMode(HornLed, OUTPUT);
  pinMode(CouplerLed, OUTPUT);
  pinMode(ExtraLed, OUTPUT);

  EncButton.begin(EncSW);
  LeftButton.begin(LeftBtn);
  RightButton.begin(RightBtn);
  UpButton.begin(UpBtn);
  DownButton.begin(DownBtn);
  LightButton.begin(LightBtn);
  HornButton.begin(HornBtn);
  CouplerButton.begin(CouplerBtn);
  ExtraButton.begin(ExtraBtn);


  LightButton.setToggleState(0);    // set initial state 0 or 1
  LightButton.setToggleTrigger(0);  // set trigger onPress: 0, or onRelease: 1

  enc.begin(EncA, EncB);
  enc.setLimits(0, 40);
}
//==============================================================================================

COROUTINE(CheckInputs) {
  COROUTINE_LOOP() {

    enc.tick();  // update encoder -> call tick() as often as possible

    EncButton.poll();
    LeftButton.poll();
    RightButton.poll();
    UpButton.poll();
    DownButton.poll();
    LightButton.poll();
    HornButton.poll();
    CouplerButton.poll();
    ExtraButton.poll();

    bool buttonState = EncButton.onRelease() + LeftButton.onRelease() + UpButton.onRelease() + RightButton.onRelease()
                       + DownButton.onRelease() + LightButton.onRelease() + HornButton.onRelease() + CouplerButton.onRelease()
                       + ExtraButton.onRelease() + EncButton.onPress() + LeftButton.onPress() + UpButton.onPress()
                       + RightButton.onPress() + DownButton.onPress() + LightButton.onPress()
                       + HornButton.onPress() + CouplerButton.onPress() + ExtraButton.onPress();

    if (buttonState) {
      ReadButtons();
      PackData();
    }
    COROUTINE_DELAY(1);
  }
}

COROUTINE(ReadEncoder) {
  COROUTINE_LOOP() {
    if (enc.valueChanged()) {
      Throttle = enc.getValue();
      Throttle = map(Throttle, 0, 40, 0, 127);
      Serial.println(enc.getValue());
      PackData();
    }
  }
}
//==============================================================================================
void ReadButtons() {

  if (UpButton.isPressed()) {
    if (Direction <= 0) enc.setValue(0);
    Throttle = 0;
    Direction = 1;
    digitalWrite(UpLed, HIGH);
    digitalWrite(DownLed, LOW);
  } else if (DownButton.isPressed()) {
    if (Direction >= 0) enc.setValue(0);
    Throttle = 0;
    Direction = -1;
    digitalWrite(UpLed, LOW);
    digitalWrite(DownLed, HIGH);
  }

  Left = LeftButton.isPressed();
  Right = RightButton.isPressed();

  Up = UpButton.isPressed();
  Down = DownButton.isPressed();

  Light = LightButton.toggle();
  digitalWrite(LightLed, Light);

  Horn = HornButton.isPressed();
  digitalWrite(HornLed, HornButton.isPressed());

  Coupler = CouplerButton.isPressed();
  digitalWrite(CouplerLed, CouplerButton.isPressed());

  Extra = ExtraButton.isPressed();
  digitalWrite(ExtraLed, ExtraButton.isPressed());
}

//==============================================================================================
void PackData() {
  rcdata.THROTTLE = Throttle;
  rcdata.DIRECTION = Direction;
  rcdata.LEFT = Left;
  rcdata.RIGHT = Right;
  rcdata.UP = Up;
  rcdata.DOWN = Down;
  rcdata.LIGHT = Light;
  rcdata.HORN = Horn;
  rcdata.COUPLER = Coupler;
  rcdata.EXTRA = Extra;
  transmitData();
}
//==============================================================================================
