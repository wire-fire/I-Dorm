long hrToMs = 3600000; //Converts hours to milliseconds
long secToMs = 1000; //Converts seconds to milliseconds
long onSec = 10; //Number of seconds pump should be on
long offHr = 12; //Number of hours pump should be off
long relayPin = 2; //Pin connected to water pump relay

void setup() {
  // put your setup code here, to run once:
  pinMode(relayPin, OUTPUT); //Pin for relay module connected to water pump
  digitalWrite(relayPin, HIGH); //Initialize low
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(relayPin, LOW); //Turn on pump
  delay(onSec*secToMs); //Delay for onSec seconds
  digitalWrite(relayPin, HIGH); //Turn off pump
  delay(offHr*hrToMs); //Delay for offHr hours
}
