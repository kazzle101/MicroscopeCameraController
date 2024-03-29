
// clear the oled char arrays - not the display
void clearOLEDtext() {

  oledText.line1[0] = {0};
  oledText.line2[0] = {0};
  oledText.line3[0] = {0};
  oledText.line4[0] = {0};
}

void oledBlankDisplay() {
  display.clearDisplay();
  display.display();  
}

// not used, I didn't like the text size
void oledTextOutputLarge() {

  display.clearDisplay();

  display.setTextSize(2);      // Normal 1:1 pixel scale
  display.setTextColor(WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  
  display.println(F(oledText.line1));
  display.println(F(oledText.line2));

  display.display();

  clearOLEDtext();
}

// display the text to screen
void oledTextOutput() {

  display.clearDisplay();

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  
  display.println(F(oledText.line1));
  display.println(F(oledText.line2));
  display.println(F(oledText.line3));
  display.println(F(oledText.line4));

  display.display();

  clearOLEDtext();
}


void oledShowMainOptions() {
  sprintf(oledText.line1,"%s", controls.opts[controls.optPos]);
  //sprintf(oledText.line2,"opt: %i, %s", controls.optPos, (enc.rotation ? " CW" : "CCW" ));
  oledTextOutput();
}
