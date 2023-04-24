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


char c = ' ';
boolean NL = true;
int interruptPin = 2; //Pin for interrupt
String test = "";

void receive_ ()
{
  //LOOKING FOR {TEMP}

  if (c == '}') {
    Serial.print(test);
    int ind1 = test.indexOf("{"); //Finds { index
    //int ind2 = test.indexOf(","); //Finds , index
    int ind3 = test.indexOf("}"); //Finds } index
    String strTemp = test.substring(ind1 + 2, ind3); //captures first data String
    //String strY = test.substring(ind2 + 1, ind3); //captures second data String
    float numTemp = strTemp.toFloat();
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
  attachInterrupt(digitalPinToInterrupt(interruptPin), receive_, CHANGE);
}

void loop()
{

}
