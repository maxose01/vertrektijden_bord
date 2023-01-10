#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>


const char* ssid = "WiFi Bussum 81";
const char* password = "#Bussum2023";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
}

void scrapeTable() {
  HTTPClient http;
  http.begin("https://www.ns.nl/stationsinformatie/gvc/den-haag-centraal");
  int httpCode = http.GET();

  if (httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    String payload = http.getString();
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);

    // find the table element
    JsonArray table = doc["ng-star-inserted"];
    Serial.println(table);

    // iterate over the rows in the table
    for (JsonObject row : table) {
      // access the cells in the row
      String cell1 = row["Tijd"];
      String cell2 = row["Richting"];
      Serial.println(cell1 + ", " + cell2);
      // do something with the cell values
    }
  }
  http.end();
}

void printWebpage() {
  HTTPClient http;
  http.begin("https://www.ns.nl/stationsinformatie/gvc/den-haag-centraal");
  int httpCode = http.GET();
  Serial.println(httpCode);
  if (httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    String payload = http.getString();
    Serial.println(payload);
  }
  http.end();
}

void loop() {
  scrapeTable();
  //printWebpage();
  delay(5000);
}