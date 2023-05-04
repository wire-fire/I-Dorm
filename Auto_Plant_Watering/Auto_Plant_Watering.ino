long secToMs = 1000; //Converts seconds to milliseconds
long onSec = 10; //Number of seconds pump should be on
long relayPin = 2; //Pin connected to water pump relay
unsigned long hold;
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
long percent;


void setup() {
  // put your setup code here, to run once:
  pinMode(relayPin, OUTPUT); //Pin for relay module connected to water pump
  digitalWrite(relayPin, HIGH); //Initialize low
  Serial.begin(9600);
  // initialize OLED display with address 0x3C for 128x64
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
}

void loop() { 
  // put your main code here, to run repeatedly:
  digitalWrite(relayPin, LOW); //Turn on pump
  delay(onSec*secToMs); //Delay for onSec seconds
  hold = millis();
  while (millis()<=(hold+43200000)) {
    digitalWrite(relayPin, HIGH); //Turn off pump
    Serial.print(millis());
    oled.clearDisplay(); // clear display
    oled.setTextSize(2);          // text size
    oled.setTextColor(WHITE);     // text color
    oled.setCursor(5, 16);        // position to display
    percent = ((millis() - hold)/432000);
    oled.print(String(percent));
    oled.print("%");
    oled.display();
  }
}

void upHold() {
  hold += 1;
  loop();
}

void downHold() {
  if (hold > 1) {
    hold -= 1;
  }
  loop();
}
