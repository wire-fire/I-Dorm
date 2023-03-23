//Refined serial communication receive method
//Created by Jack McTasney
//Functions of interest: serial.readbytesuntil(char, val, len), serial.readstring()

const int maxSize = 50;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  String receive;
  int len;
  char c[maxSize];
  if (Serial.available())
  {
    len = Serial.readBytesUntil('}', c, maxSize);
    receive = Serial.readString();
  }
  for (int count = 0; count < len; count++)
  {
    Serial.print(c[count]);
  }
  Serial.print(" | ");
  Serial.println(receive);
}
