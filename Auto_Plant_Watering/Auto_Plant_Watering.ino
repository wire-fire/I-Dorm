long secToMs = 1000; //Converts seconds to milliseconds
long onSec = 10; //Number of seconds pump should be on
long relayPin = 2; //Pin connected to water pump relay
unsigned long hold;

void setup() {
  // put your setup code here, to run once:
  pinMode(relayPin, OUTPUT); //Pin for relay module connected to water pump
  digitalWrite(relayPin, HIGH); //Initialize low
}

void loop() { 
  // put your main code here, to run repeatedly:
  digitalWrite(relayPin, LOW); //Turn on pump
  delay(onSec*secToMs); //Delay for onSec seconds
  hold = millis();
  while (millis()<=(hold+43200000)) {
    digitalWrite(relayPin, HIGH); //Turn off pump
  }
}
