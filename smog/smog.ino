#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "view.h"
#include "meter.h"
#include "wificreds.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

const char* ssid = APSSID2;
const char* password = APPSK;

const float MAX_SCALE = 250;
char buffer[25];

//Your Domain name with URL path or IP address with path
String serverName = "http://txtin.gs/aqi";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 1000 * 60 * 30;
bool starting = true;
void setup() {
  Serial.begin(115200);
  meterSetup();
  viewSetup();
  wiggle();
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(450);
    Serial.print(".");
    analogWrite(meter, 120);
    delay(50);
    analogWrite(meter, 140);
  }
  clear();
  print("connected.");
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
  wiggle();
}

void loop() {
  //Send an HTTP POST request every 10 minutes
  if (starting | (millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      starting = false;
      HTTPClient http;

      String serverPath = serverName;

      // Your Domain name with URL path or IP address with path
      http.begin(serverPath.c_str());

      // Send HTTP GET request
      int httpResponseCode = http.GET();

      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        payload.toCharArray(buffer, 25);
        clear();
        print(buffer);
        Serial.println(payload);
        Serial.println(payload.toInt());
        setLevel((float)payload.toInt());
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
        wiggle();
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
