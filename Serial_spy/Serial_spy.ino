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
  attachInterrupt(digitalPinToInterrupt(2), blink_, CHANGE);
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
  for (int i = 0;i<=255;i++){
    oled.clearDisplay(); // clear display
    oled.setTextSize(2);          // text size
    oled.setTextColor(WHITE);     // text color
    oled.setCursor(5, 16);        // position to display
    oled.print(i);
    Serial.print(i);
    delay(100);
  }
}

void blink_ ()
{
  char c;
  String test =  "";
  //Serial.println("I AM HERE");
  
    c = Serial.read();
    test += c;
    oled.clearDisplay(); // clear display
    oled.setTextSize(1);          // text size
    oled.setTextColor(WHITE);     // text color
    oled.setCursor(5, 16);        // position to display
    Serial.print(test);
    oled.println(test);
    oled.display();


}
