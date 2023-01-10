#include <HTTPClient.h>
#include "credentials.h"
#include <WiFi.h>
#include <ArduinoJson.h>

const char* BASE_URL = "https://api.vertrektijd.info/departures/_nametown/";
const char* api_key = "X-Vertrektijd-Client-Api-Key";

void setup() {
  Serial.begin(115200);
  // Connect to Wi-Fi
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println(WiFi.status());

  String full_url = String(BASE_URL) + String(TOWN) + "/" + String(STOP) + "/";

   // Make the API request
  HTTPClient http;
  http.begin(full_url);
  http.addHeader(api_key, API_KEY);
  int httpCode = http.GET();
  if (httpCode > 0) {
    String response = http.getString();
    StaticJsonDocument<2048> doc;
    DeserializationError error = deserializeJson(doc, response);
    if(!error){
      JsonArray departures = doc["BTMF"][0]["Departures"];
      Serial.println(departures);
      for (JsonObject departure : departures) {
          String lineNumber = departure["LineNumber"];
          String destination = departure["Destination"];
          String expectedDeparture = departure["ExpectedDeparture"];
          Serial.println("Line Number: " + lineNumber + " Destination: " + destination + " Expected Departure: " + expectedDeparture);
      }
    } else {
      Serial.println("Error with JSON object");
    }
  } else {
    Serial.println("Error: " + String(httpCode));
  }
  http.end();
  delay(1000);
}

void loop() {
  // Do nothing
}