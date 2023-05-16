#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
long percent;
unsigned long hold;
void setup() {
  Serial.begin(9600);
  // initialize OLED display with address 0x3C for 128x64
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
}


void loop() {
  hold = millis();
  while (millis() <= (hold + 10000)) {
    oled.clearDisplay(); // clear display
    oled.setTextSize(2);          // text size
    oled.setTextColor(WHITE);     // text color
    oled.setCursor(5, 16);        // position to display
    percent = ((millis() - hold)/100);
    oled.print(percent);
    oled.print("%");
    oled.print("(=OwO=)");
    oled.display();
    Serial.print(percent);
    Serial.print(" | ");
    Serial.print(millis());
    Serial.print(" | ");
    Serial.println((((millis() - hold) / 10000)*100));
    delay(100);
  }
}
