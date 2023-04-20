int hrToMs = 3600000; //Converts hours to milliseconds
int secToMs = 1000; //Converts seconds to milliseconds
int onSec = 10; //Number of seconds pump should be on
int offHr = 12; //Number of hours pump should be off
int relayPin = 2; //Pin connected to water pump relay

void setup() {
  // put your setup code here, to run once:
  pinMode(relayPin, OUTPUT); //Pin for relay module connected to water pump
  digitalWrite(relayPin, LOW); //Initialize low
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(relayPin, HIGH); //Turn on pump
  delay(onSec*secToMs); //Delay for onSec seconds
  digitalWrite(relayPin, LOW); //Turn off pump
  delay(offHr*hrToMs); //Delay for offHr hours
}
