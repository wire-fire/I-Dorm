//ErMo Joystick Transmitter Code
//Written by Jack McTasney
//Based off of example from https://www.pjrc.com/teensy/td_libs_AltSoftSerial.html

#include <AltSoftSerial.h>
AltSoftSerial BTserial;
// https://www.pjrc.com/teensy/td_libs_AltSoftSerial.html


char c = ' ';
boolean NL = true;
int x = A0;
int y = A1;
int joystickX = 0; //Holds joystick x value for transmission
int joystickY = 0; //Holds joystick y value for transmission

void setup()
{
  pinMode(x, INPUT);
  pinMode(y, INPUT);
  Serial.begin(9600);
  Serial.print("Sketch:   ");   Serial.println(__FILE__);
  Serial.print("Uploaded: ");   Serial.println(__DATE__);
  Serial.println(" ");
  BTserial.begin(9600);
  Serial.println("BTserial started at 9600");
  //Initialization protocol version 1
  BTserial.print("AT");
  delay(1000);
  BTserial.print("AT+CO094A9A83AED70");
  delay(1000);
  BTserial.print("AT+CO094A9A83AED70");
  delay(1000);
  BTserial.print("AT+CO094A9A83AED70");
}

void loop()
{
  // Read from the Bluetooth module and send to the Arduino Serial Monitor
  if (BTserial.available())
  {
    c = BTserial.read();
    Serial.write(c);
  }
  /*
  //Attempt 1 at an in-loop connection protocol
  if (BTserial.available() != true) //If connection is unavailable for 1 second, begin connection protocol
  {
    delay(1000);
    if (BTserial.available() != true)
    {
      BTserial.print("AT");
      delay(500);
      BTserial.print("AT+CO094A9A83AED70");
      delay(500);
      BTserial.print("AT+CO094A9A83AED70");
      delay(500);
      BTserial.print("AT+CO094A9A83AED70");
    }
  }
*/

  // Read from the Serial Monitor and send to the Bluetooth module
  if (Serial.available())
  {
    c = Serial.read();

    // do not send line end characters to the HM-10
    if (c != 10 & c != 13 )
    {
      BTserial.write(c);
    }

    // Echo the user input to the main window.
    // If there is a new line print the ">" character.
    if (NL) {
      Serial.print("\r\n>");
      NL = false;
    }
    Serial.write(c);
    if (c == 10) {
      NL = true;
    }
  }
  joystickX = map(analogRead(x), 0, 1023, 0, 99);
  joystickY = map(analogRead(y), 0, 1023, 0, 99);
  Serial.print("{");
  Serial.print(joystickX);
  Serial.print(",");
  Serial.print(joystickY);
  Serial.print("}");
  Serial.print("\n");
  BTserial.print("{");
  BTserial.print(joystickX);
  BTserial.print(",");
  BTserial.print(joystickY);
  BTserial.print("} "); //Includes a space to avoid packet deformation
  delay(40);
}
