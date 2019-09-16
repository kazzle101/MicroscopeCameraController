

// common header for all the mouse control
void macroHead() {
  sprintf(oledText.line1, "Set %s", menuTitle);
  oledTextOutput();
  Mouse.moveTo(0, 0);
  delay(controls.optDelay);

}

// common scroll wheel function
void macroScrollWheel() {

  int xx = 0;

  while (true) {
    currentTime = millis();
    if (currentTime >= (loopTime + 5)) {
      readRotaryEncoder();
      loopTime = currentTime;
    }
    readRotaryButton();    
    if (enc.isRotaryBtn) {
      sprintf(oledText.line1, "Exit %s", menuTitle);
      enc.isRotaryBtn = false;
      break;
    }

    if (enc.isRotating)
    {
      digitalWrite(MONITOR_LED, HIGH);

      scrollWheel = (enc.rotation ? controls.optWheel : -controls.optWheel);
      sprintf(oledText.line1, "Set %s", menuTitle);
      sprintf(oledText.line2, "%i, %i", xx, scrollWheel);
      oledTextOutput();

      Mouse.scroll(scrollWheel);
      //        Mouse.move(0,0,scrollWheel);

      enc.isRotating = false;
      digitalWrite(MONITOR_LED, LOW);
      delay(controls.optDelay);
      xx++;
    }
  }

  
}


void macroSetManualFocus(boolean adjustFocus) {

  macroHead();
  Mouse.moveTo(controls.mf[1], controls.mf[2]);
  delay(controls.optDelay);
  Mouse.click(MOUSE_LEFT);
  delay(controls.optDelay);

  if (!adjustFocus) {
    return;
  }
  
  Mouse.moveTo(controls.mfSelect[1], controls.mfSelect[2]);
  delay(controls.optDelay);
  Mouse.click(MOUSE_LEFT);
  delay(controls.optDelay);
  macroScrollWheel();

}

void macroSetAutoFocus() {

  macroHead();
  Mouse.moveTo(controls.af[1], controls.af[2]);
  delay(controls.optDelay);
  Mouse.click(MOUSE_LEFT);

}

void macroSetClickAF() {

  macroHead();
  Mouse.moveTo(controls.clickAF[1], controls.clickAF[2]);
  delay(controls.optDelay);
  Mouse.click(MOUSE_LEFT);

}


void macroSetExposureBrightness() {

  // click AE then click for Bright slider
  macroHead();
  Mouse.moveTo(controls.expAE[1], controls.expAE[2]);
  delay(controls.optDelay);
  Mouse.click(MOUSE_LEFT);
  delay(controls.optDelay);
  Mouse.moveTo(controls.expBright[1], controls.expBright[2]);
  delay(controls.optDelay);
  Mouse.click(MOUSE_LEFT);
  delay(controls.optDelay);
  macroScrollWheel();
}

void macroSetExposureGain() {

  macroHead();
  Mouse.moveTo(controls.expME[1], controls.expME[2]);
  delay(controls.optDelay);
  Mouse.click(MOUSE_LEFT);
  delay(controls.optDelay);
  Mouse.moveTo(controls.expGain[1], controls.expGain[2]);
  delay(controls.optDelay);
  Mouse.click(MOUSE_LEFT);
  delay(controls.optDelay);
  macroScrollWheel();

}


// when the button on the rotary encoder has been pressed
void macroRun(int opt) {

  digitalWrite(MONITOR_LED,LOW);
  enc.isRotaryBtn = false;
  menuTitle[0] = {0};
  strcat(menuTitle, controls.opts[opt]);

  btns.value = 0;
  switch (opt) {
    case (0):
      setRGBcolour(enc.colours[opt+1]); 
      macroSetManualFocus(true);
      break;
    case (1):
      setRGBcolour(enc.colours[opt+1]); 
      macroSetAutoFocus();
      break;
    case (2):
      setRGBcolour(enc.colours[opt+1]); 
      macroSetClickAF();
      break;
    case (3):
      setRGBcolour(enc.colours[opt+1]); 
      macroSetExposureBrightness();
      break;
    case (4):
      setRGBcolour(enc.colours[opt+1]); 
      macroSetExposureGain();
      break;

    default:
      setRGBcolour(enc.colours[7]); 
      Serial.println("macroRun NOT DEFINED");
      break;
  }

  enc.isRotaryBtn = false;
  delay(30);
  Mouse.moveTo(camera.resolution[0], camera.resolution[1]);  // move the mouse cursor out of the way
  btns.value = 0;
  setRGBcolour(enc.colours[0]); 
}


// when one of the buttons has been pressed
void macroButtonRun(byte opt) {

//    Serial.print("macro button: ");
//    Serial.println(opt);

    digitalWrite(MONITOR_LED,LOW);
    menuTitle[0] = {0};

    switch (opt) {
      case(1):       // BTN1   
        mcp0.digitalWrite(btns.buttonLEDs[0], LOW);   
        strcat(menuTitle, controls.opts[2]);
        macroSetClickAF();
        break;
      case(2):      // BTN2
        mcp0.digitalWrite(btns.buttonLEDs[1], LOW);        
        strcat(menuTitle, controls.opts[0]);
        macroSetManualFocus(false);
        break;
      case(4):     // BTN3
        mcp0.digitalWrite(btns.buttonLEDs[2], LOW);        
        strcat(menuTitle, controls.opts[1]);
        macroSetAutoFocus();
        break;
      
      case(8):     // BTN4
      default:
        break;
    }

    enc.isRotaryBtn = false;
    delay(30);
    Mouse.moveTo(camera.resolution[0], camera.resolution[1]);
    btns.value = 0;
    clearButtonLEDs();  
}
