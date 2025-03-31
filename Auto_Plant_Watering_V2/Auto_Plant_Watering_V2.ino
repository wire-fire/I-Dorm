long secToMs = 1000;           //Converts seconds to milliseconds
long onSec = 10;               //Number of seconds pump should be on
long relayPin = 2;             //Pin connected to water pump relay
#define up 9                   //Pin for up switch
#define down 10                // Pin for down switch
unsigned long holdTime;        // long to hold time value
unsigned long hold = 3600000;  //holds number of ms to stay on (3,600,000 ms per 1 hour)
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128  // OLED display width,  in pixels
#define SCREEN_HEIGHT 32  // OLED display height, in pixels
// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
long percent;
int signifier = 0;  //Used to signify up or down


void setup() {
  // put your setup code here, to run once:
  pinMode(relayPin, OUTPUT);     //Pin for relay module connected to water pump
  digitalWrite(relayPin, HIGH);  //Initialize low
  Serial.begin(9600);
  pinMode(up, INPUT);  //Switch pins
  pinMode(down, INPUT);
  attachInterrupt(digitalPinToInterrupt(up), upHold, RISING);  //Defining switch pins as interrupts with ISRs below loop fxn
  attachInterrupt(digitalPinToInterrupt(down), downHold, RISING);
  // initialize OLED display with address 0x3C for 128x64
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(relayPin, LOW);   //Turn on pump
  delay(5000);                   //Delay for onSec seconds
  digitalWrite(relayPin, HIGH);  //Turn off pump
  holdTime = millis();
  while (millis() <= (holdTime + hold)) {
    if (signifier == 1) {
      hold += 3600000;
      signifier = 0;
    } else if (signifier == 2) {
      if (hold > 3600000) {
        hold -= 3600000;
      }
      signifier = 0;
    }
    Serial.println(hold / 3600000);
    oled.clearDisplay();       // clear display
    oled.setTextSize(2);       // text size
    oled.setTextColor(WHITE);  // text color
    oled.setCursor(5, 16);     // position to display
    percent = ((millis() - holdTime) / (hold / 100));
    oled.print(String(percent));
    oled.print("%");
    oled.print(" Hrs:");
    oled.print(hold / 3600000);
    oled.display();
  }
}

void upHold() {
  signifier = 1;
}

void downHold() {
  signifier = 2;
}
