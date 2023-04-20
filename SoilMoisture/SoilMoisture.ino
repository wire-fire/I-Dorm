int soilPin = A0;
int soil = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(soilPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  soil = analogRead(soilPin);
  Serial.println(soil);
  delay(100);
}
