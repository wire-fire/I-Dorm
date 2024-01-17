#include <OneWire.h> //OneWire Library
#include <DallasTemperature.h> //Temperature Library
#include <AltSoftSerial.h> //Bluetooth Library

// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
AltSoftSerial BTserial; //D8 is Rx, D9 is Tx

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
float temp; //Hold temp value for sending
void setup(void)
{
// start serial port
Serial.begin(9600);
BTserial.begin(9600);
Serial.println("Dallas Temperature IC Control Library Demo");
//Connection protocol
BTserial.print("AT");
delay(500);
BTserial.print("AT+CO094A9A83AB93C");
// Start up the library
sensors.begin(); // IC Default 9 bit. If you have troubles consider upping it 12. Ups the delay giving the IC more time to process the temperature measurement
}

void loop(void)
{
// call sensors.requestTemperatures() to issue a global temperature
// request to all devices on the bus
sensors.requestTemperatures(); // Send the command to get temperatures

//Code from example (explains the index thing)

//Serial.print("Temperature for Device 1 is: ");
//Serial.print(sensors.getTempFByIndex(0)); // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire

//My code :)


temp=sensors.getTempFByIndex(0);
//Serial print
Serial.print("{");
Serial.print(temp);
Serial.print("}");
//Bluetooth print
BTserial.print("{");
BTserial.print(temp);
BTserial.print("}");

delay(1000);
}
