#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>

AsyncWebServer server(65);

const char ssid = "Jack is fucking with WiFi";
const char pass = "eatmyshorts";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); //Native 115200 baud of ESP8266
  WiFi.softAP(ssid,pass); //(SSID, Password > 8 characters)
  pinMode(14, OUTPUT);

  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readTemp().c_str());
  });
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (WiFi.softAPgetStationNum() >= 1)
  {
    Serial.println("You did the thing");
    digitalWrite(14, HIGH);
  }
  else
  {
    Serial.println("Nobody is home");
    digitalWrite(14, LOW);
  }
}
