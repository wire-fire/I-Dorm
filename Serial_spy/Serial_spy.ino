#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
String serialStore = " ";
char serial;
void setup() {
  Serial.begin(9600);
  // initialize OLED display with address 0x3C for 128x64
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
  delay(2000);
}

void loop() {
/*
  if (Serial.available())
  {
    serial = Serial.read();
    serialStore += String(serial);
    delay(4);
  }
  else
  {
  */
    //Serial.println(serialStore);
    oled.clearDisplay(); // clear display
    oled.setTextSize(1);          // text size
    oled.setTextColor(WHITE);     // text color
    oled.setCursor(5, 16);        // position to display
    oled.println("Hello World"); // text to display
    oled.display();               // show on OLED
    //serialStore = "";
    delay(100);
 // }
}
