

// for Teensy 3.2
// in Ardunio IDE in Tools set the USB Type: Serial + Keyboard + Mouse + Joystick

#include <SPI.h>
#include <Wire.h>
#include "Adafruit_MCP23017.h"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     3 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define INTA 5   // using pin 2 for interrupt A on an Ardunio UNO
#define MONITOR_LED LED_BUILTIN

Adafruit_MCP23017 mcp0;
char pout[120] = {0};
byte maxNumber = 0;
int scrollWheel = 0;
char menuTitle[21] = {0};
unsigned long currentTime;
unsigned long loopTime;

#include "microscope_controller_val.h"
ENCODER enc;
BUTTONS btns;
OLEDTEXT oledText;
CAMERA camera;
CONTROLS controls;
#include "encoder_functions.h"
#include "oled_functions.h"
#include "macro_functions.h"


void setup() {

  Mouse.begin();
  Mouse.screenSize(camera.resolution[0], camera.resolution[1]);

  delay(1000);
  Serial.begin(9600);
  Serial.println("ready");

  pinMode(MONITOR_LED, OUTPUT);
  digitalWrite(MONITOR_LED, HIGH);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  // Clear the buffer
  display.clearDisplay();

  Serial.println("ready");

  mcp0.begin(0);      // 0 = i2c address 0x20

  // setup GPA for input
  for (byte n = 0; n <= 7; n++) {
    mcp0.pinMode(n, INPUT);
    mcp0.pullUp(n, HIGH);  // turn on the internal 100K pullup
  }

  // setup GPB for output
  for (byte n = 8; n <= 15; n++) {
    mcp0.pinMode(n, OUTPUT);
    mcp0.digitalWrite(n, HIGH); // turn LEDS off'
  }

  // show the available colours on the RGB led
  for (byte i=0; i < 9; i++) {
      setRGBcolour(enc.colours[i]);
      delay(250);    
  }
  setRGBcolour(enc.colours[0]);

  Serial.println("setup OK");
  digitalWrite(MONITOR_LED, LOW);
  oledShowMainOptions();
  delay(500);

  oledText.blankMillis = millis() + oledText.blankDelay;
}

void loop() {
  currentTime = millis();

  // scan for buttons being pressed, rotary encoder being turned
  if (currentTime >= (loopTime + 5)) {
    readRotaryEncoder();
    readRotaryButton();
    readButtons();
    loopTime = currentTime;
  }

  // blank the display afer a certain amount of time
  if (currentTime >= oledText.blankMillis && oledText.screenBlank == false) {
    //setRGBcolour(enc.colours[5]);
    oledBlankDisplay();    
    oledText.screenBlank = true;
    oledText.blankMillis = currentTime + oledText.blankDelay;    
  }

  // blink an LED occasionally while the display is blank
  if (((currentTime - oledText.blinkyMillis) >= oledText.blinkyPeriod) && oledText.screenBlank == true) {
    oledText.blinkyPeriod = (oledText.blinkyLED ? oledText.blinky[1] : oledText.blinky[0]);
    oledText.blinkyLED = !(oledText.blinkyLED);
    oledText.blinkyMillis = currentTime;
    digitalWrite(MONITOR_LED, oledText.blinkyLED);
  }

  // things to do when a button is pressed
  if (btns.value != 0) {
    macroButtonRun(btns.value);
    oledShowMainOptions();
    btns.value=0;    
    oledText.screenBlank = false;
  }
  
  // when the button the the rotary encoder is clicked
  if (enc.isRotaryBtn) {
    macroRun(controls.optPos);
    oledShowMainOptions();
    enc.isRotaryBtn = false;
    oledText.screenBlank = false;

  }

  // when the rotary encoder is being turned
  if (enc.isRotating) {    
    digitalWrite(MONITOR_LED, HIGH);
    if (enc.rotation) {
      setRGBcolour(enc.colours[5]);
      controls.optPos ++;
    }
    else {
      setRGBcolour(enc.colours[3]);
      controls.optPos --;
    }
    controls.optPos = (controls.optPos < 0 ? 0 : controls.optPos);
    controls.optPos = (controls.optPos > controls.optMax ? controls.optMax : controls.optPos);

    oledShowMainOptions();

    enc.isRotating = false;
    delay(40);
    digitalWrite(MONITOR_LED, LOW);
    setRGBcolour(enc.colours[0]);
    oledText.screenBlank = false;
  }


}
