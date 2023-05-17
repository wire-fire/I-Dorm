/*
  This should be fun
  Written by Jack McTasney
  5-16-23
  128x64 OLED / Adafruit Trellis Integration
*/

/*
  TRELLIS INFO (Wire and Adafruit_Trellis libraries)
  Call Adafruit_Trellis & Adafruit_TrellisSet as seen below first
  readSwitches() - Reads switch data
  justPressed() - Checks to see if a switch was just pressed after readSwitches() was called
  justReleased() - Checks to see if switch was just released after readSwitches() was called
  setLED(switch#) - Turns on corresp. switch LED
  clrLED(switch#) - Turns off corresp. switch LED
  isLED(switch#) - Used in logic statements, checks if LED is on or off (returns 1 or true idk which one if LED is on)
  writeDisplay() - Writes updated LED data to trellis
  begin(ADDR) - Begins OLED communication, use 0x70 for 1 display (0x71, 0x72, 0x73 for other connected ones)
*/

/*
  OLED INFO (Wire, Adafruit_GFX, and Adafruit_SSD1306 libraries)
  Call this first Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
  SCREEN_WIDTH is set to 128, SCREEN_HEIGHT is set to 64
  clearDisplay() - Clears display
  setTextSize(#) - Sets text size
  setTextColor(Color) - Sets text color if you're fancy like that
  oled.setCursor(x,y) - Sets cursor position on display
  print(something) - Prints something to the OLED
  display() - Displays what has been printed to the OLED
  begin(SSD1306_SWITCHCAPVCC, ADDR) - begins OLED communication, default ADDR is 0x3C
*/
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Trellis.h>
#define SCREEN_WIDTH 128  // OLED display width,  in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
//Trellis Time
Adafruit_Trellis matrix0 = Adafruit_Trellis();
Adafruit_TrellisSet trellis = Adafruit_TrellisSet(&matrix0);
#define NUMTRELLIS 1

#define numKeys (NUMTRELLIS * 16)


long percent;
unsigned long hold;
void setup() {
  Serial.begin(9600);
  // initialize OLED display with address 0x3C for 128x64
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true)
      ;
  }
  trellis.begin(0x70);
  //Test for trellis, lights up then turns off all LEDs in order
  for (uint8_t i = 0; i < numKeys; i++) {
    trellis.setLED(i);
    trellis.writeDisplay();
    delay(50);
  }
  for (uint8_t i = 0; i < numKeys; i++) {
    trellis.clrLED(i);
    trellis.writeDisplay();
    delay(50);
  }
}


void loop() {
  delay(30);
  //OLED initialization
  oled_reset();
  trellis.clear();
  //Constantly reads for switch state, when pressed
  while (trellis.readSwitches()) {
    for (uint8_t i = 0; i < numKeys; i++) {
      if (trellis.justPressed(i)) {
        oled_reset();
        oled.print(i);
        oled.display();
        trellis.setLED(i);
        Serial.println("Pressed");
      }
      if (trellis.justReleased(i)) {
        oled_reset();
        oled.print("CLEAR");
        oled.display();
        trellis.clrLED(i);
      }
    }
    trellis.writeDisplay();
  }
}
// Hopefully this unfucks the issue where the cursor goes to narnia if you move too fast
// IT DOES!!!!!!!!!!!!!
void oled_reset() { 
    oled.clearDisplay();  // clear display
    oled.setTextSize(2);       // text size
    oled.setTextColor(WHITE);  // text color
    oled.setCursor(5, 16);     // position to display
  }
