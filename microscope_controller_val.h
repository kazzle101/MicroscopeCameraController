
// almost all the confiuration is here

struct ENCODER {

  const byte rotaryAB[2] = {1, 0};  // MCP23017 GPA input pins
  const byte rotaryBtn = 2;         // MCP23017 GPA input pins
  const byte rotaryLED[3] = { 15, 14, 13};  // MCP23017 GPB output pins - R G B

  boolean colours[8][3] = { {1, 1, 1},  // 0 off (black)
                            {1, 1, 0},  // 1 red      
                            {1, 0, 1},  // 2 green  
                            {1, 0, 0},  // 3 yellow     
                            {0, 1, 1},  // 4 blue     
                            {0, 1, 0},  // 5 magenta          
                            {0, 0, 1},  // 6 cyan 
                            {0, 0, 0}}; // 7 white    

  boolean rotation = false; // true = clockwise, false = anticlockwise
  boolean lastRotation = false;
  boolean isRotating = false;
  boolean isRotaryBtn = false;
  byte rotaryAprev = 0;
                                   
};

/*
 *       LED                 Buttons
 *       8  - GPB0  --       7 - GPA7  --
 *       9  - GPB1  LED2     6 - GPA6  BTN1
 *       10 - GPB2  LED3     5 - GPA5  BTN4
 *       11 - GPB3  LED1     4 - GPA4  BTN3
 *       12 - GPB4  LED4     3 - GPA3  BTN2
 *       13 - GPB5  Blue     2 - GPA2  Rotary SW
 *       14 - GPB6  Green    1 - GPA1  Rotary A
 *       15 - GPB7  Red      0 - GPA0  Rotary B
 */


struct BUTTONS {

  const byte numberOfButtons = 4;

  const byte buttonPins[4] = { 6, 3, 4, 5};     // MCP23017 GPA input pins
  const byte buttonLEDs[4] = { 11, 9, 10, 12};  // MCP23017 GPB output pins

  byte lastValue = 0;
  byte value = 0;
};

struct OLEDTEXT {
  const unsigned long blankDelay = 120 * 1000;  // two minutes
  unsigned long blankMillis;
  boolean screenBlank = false;

  // blink an LED occasionally while the display is blank
  const unsigned long blinky[2] = { 120, 8000 }; // onTime, offTime
  unsigned long blinkyMillis = 0;
  unsigned long blinkyPeriod = blinky[0];
  boolean blinkyLED = true;
  
  
  char line1[21] = {0};
  char line2[21] = {0};
  char line3[21] = {0};
  char line4[21] = {0};
  
};

struct CAMERA {
  const int resolution[2] = { 1920, 1080 };
  int x = 0;
  int y = 0;
};


struct CONTROLS {  
  const char opts[5][16] = { "Manual Focus", "Auto Focus", "Click Focus", "Exp. Bright", "Exp. Gain" };  
  int optPos = 0;
  int optMax = 5-1;
  int optDelay = 250; 
  int optWheel = 2;

  // location of the camera controls, where to click on the screen
  // array = {type, x, y}
  // type:     1 = button, 2 = slider, 3 = radio, 4 = number up/down (not used)
  // location: x, y
  int mfSelect[3] = {2, 64, 25};
  int af[3] = {1, 40, 35 };
  int clickAF[3] = {1, 84, 35 };
  int mf[3] = { 1, 128, 35 };  
  int expBright[3] = {2, 80, 105 };
  int expGain[3] = {2, 80, 115 };
  int expAE[3] = { 1, 35, 130 };
  int expME[3] = { 1, 128, 130 };
  
};
