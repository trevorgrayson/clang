#include <WiFiClient.h>
#include <Arduino.h>
#include "wificreds.h"
#include "view.h"

const char* ssid = APSSID2;
const char* password = APPSK;

char buffer[25];

//Your Domain name with URL path or IP address with path
String serverName = "http://txtin.gs/aqi";

void wifiSetup() {
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(450);
    //analogWrite(meter, 120);
    delay(50);
    //analogWrite(meter, 140);
  }
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

int isOnline() {
  return WiFi.status() == WL_CONNECTED;
}

float request() {
  HTTPClient http;
  int result = -1; 

  String serverPath = serverName;

  // Your Domain name with URL path or IP address with path
  http.begin(serverPath.c_str());

  // Send HTTP GET request
  int httpResponseCode = http.GET();
  if (httpResponseCode>0) {
    String payload = http.getString();
    payload.toCharArray(buffer, 25);
    Serial.println(payload);
    result = payload.toInt();
  } else {
    print("ugh");
  }

  // Free resources
  http.end();
  return (float)result;
}
