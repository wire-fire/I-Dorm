#include <ESP8266WiFi.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); //Native 115200 baud of ESP8266
  WiFi.begin("Jack is fucking with WiFi", "eatmyshorts")
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client;
  client.connect(

}
