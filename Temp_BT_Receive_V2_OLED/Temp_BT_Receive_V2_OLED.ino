//  SerialIn_SerialOut_HM-10_01
//
//  Uses hardware serial to talk to the host computer and AltSoftSerial for communication with the bluetooth module
//
//  What ever is entered in the serial monitor is sent to the connected device
//  Anything received from the connected device is copied to the serial monitor
//  Does not send line endings to the HM-10
//
//  Pins
//  BT VCC to Arduino 5V out.
//  BT GND to GND
//  Arduino D8 (SS RX) - BT TX no need voltage divider
//  Arduino D9 (SS TX) - BT RX through a voltage divider (5v to 3.3v)
//

#include <AltSoftSerial.h>
AltSoftSerial BTserial;
// https://www.pjrc.com/teensy/td_libs_AltSoftSerial.html
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

char c = ' ';
boolean NL = true;
int interruptPin = 2; //Pin for interrupt
String test = "";
float numTemp;

void receive_ ()
{
  //LOOKING FOR {TEMP}

  if (c == '}') {
    Serial.print(test);
    Serial.print("I am here");
    int ind1 = test.indexOf("{"); //Finds { index
    //int ind2 = test.indexOf(","); //Finds , index
    int ind3 = test.indexOf("}"); //Finds } index
    String strTemp = test.substring(ind1 + 2, ind3); //captures first data String
    //String strY = test.substring(ind2 + 1, ind3); //captures second data String
    numTemp = strTemp.toFloat();
    //int ch2Width = strY.toInt();
    Serial.print("The temperature is: ");
    Serial.println(numTemp);
    test = "";
    c = ' ';
  }
  else
  {
    while (BTserial.available())
    {
      c = BTserial.read();
      test += c;
    }
  }
}

void setup()
{
  Serial.begin(9600);
  Serial.print("Sketch:   ");   Serial.println(__FILE__);
  Serial.print("Uploaded: ");   Serial.println(__DATE__);
  Serial.println(" ");

  BTserial.begin(9600);
  Serial.println("BTserial started at 9600");
  //Interrupt setup
  attachInterrupt(digitalPinToInterrupt(interruptPin), receive_, CHANGE);
  //OLED setup
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
  Serial.println("OLED is ready");
}

void loop()
{
  //OLED display
    oled.clearDisplay(); // clear display
    oled.setTextSize(1.5);          // text size
    oled.setTextColor(WHITE);     // text color
    oled.setCursor(5, 16);        // position to display
    oled.print("Temp: ");
    oled.print(numTemp);
    oled.print(" F");
    oled.display();
}
