#include <HTTPClient.h>
#include "credentials.h"
#include <WiFi.h>

const char* api_url = "https://api.vertrektijd.info/departures/_nametown/Den%20Haag/valkenboslaan/";
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

   // Make the API request
  HTTPClient http;
  http.begin(api_url);
  http.addHeader(api_key, API_KEY);
  int httpCode = http.GET();
  if (httpCode > 0) {
    String response = http.getString();
    Serial.println(response);
    //Serial.println("Success: " + String(httpCode));
  } else {
    Serial.println("Error: " + String(httpCode));
  }
  http.end();
  delay(1000);
}

void loop() {
  // Do nothing
}