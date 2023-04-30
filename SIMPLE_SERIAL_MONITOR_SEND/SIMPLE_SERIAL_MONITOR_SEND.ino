void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  char c;
  if (Serial.available())
  {
    c = Serial.read();
    Serial.print(c);
  }
}
