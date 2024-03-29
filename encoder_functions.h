

// displays the RGB colour in the rotary encoder,
void setRGBcolour(boolean colour[]) {

  for (int i = 0; i < 3; i++) {
    mcp0.digitalWrite(enc.rotaryLED[i], colour[i]);
  }
}

// read the encoder
void readRotaryEncoder() {

  byte rotA = mcp0.digitalRead(enc.rotaryAB[0]);
  byte rotB = mcp0.digitalRead(enc.rotaryAB[1]);

  if ((!rotA) && (enc.rotaryAprev)) {
    if (rotB) {
      enc.rotation = true;
    }
    else {
      enc.rotation = false;
    }
    enc.isRotating = true;

  }
  enc.rotaryAprev = rotA;
} 

// read the encoder button
void readRotaryButton() {

    boolean b = mcp0.digitalRead(enc.rotaryBtn);  

    if (!b) {
      enc.isRotaryBtn = false;
      return;
    }

    while (b == true) {
      b = mcp0.digitalRead(enc.rotaryBtn);
      delay(5);
    }

    enc.isRotaryBtn = true;
}

// turn all LEDs off
void clearButtonLEDs() {
  for (byte n = 0; n < btns.numberOfButtons; n++) {
    mcp0.digitalWrite(btns.buttonLEDs[n], HIGH); // turn LEDS off'
  }
  
}

// read the buttons - multiple buttons can be pressed
byte readButtonsGetValue() {

  bool p;
  byte enc = 0;

  for (byte n = 0; n < btns.numberOfButtons; n++) {
    p = !(mcp0.digitalRead(btns.buttonPins[n]));
    enc |= (byte)p << n;
  }

  return enc;
}

// read the buttons - this waits until the button has been relesed
void readButtons() {
  byte btn = readButtonsGetValue();
  if (btn == 0) {
    btns.value = 0;
    return;
  }

  byte b = btn;
  while (btn == b) {
    b = readButtonsGetValue();
    delay(2);
  }
  
  btns.value = btn;
  return;
}
