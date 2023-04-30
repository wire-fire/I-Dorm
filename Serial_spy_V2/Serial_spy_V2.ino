#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
char c;
String hold = "";


void serialToOLED (char firstchar) {
  delay(100); //Let register fill
  hold = firstchar;
  oled.clearDisplay(); // clear display
  oled.setTextSize(2);          // text size
  oled.setTextColor(WHITE);     // text color
  oled.setCursor(10, 16);        // position to display
  while (Serial.available()>0) {
    c = Serial.read();
    hold += c;
  }
  Serial.print(hold);
  oled.print(hold);
  oled.display();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // initialize OLED display with address 0x3C for 128x64
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()>0) {
    serialToOLED(Serial.read());
  }
}
