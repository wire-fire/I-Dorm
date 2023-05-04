#define up 11
#define down 12

unsigned long hold = 1;



void setup() {
  // put your setup code here, to run once:
  pinMode(up, INPUT);
  pinMode(down, INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(up), upHold, RISING);
  attachInterrupt(digitalPinToInterrupt(down), downHold, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(hold);
}

void upHold() {
  hold += 1;
  loop();
}

void downHold() {
  if (hold > 1) {
    hold -= 1;
  }
  loop();
}
