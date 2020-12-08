#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "view.h"
#include "wifi.h"
#include "meter.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

char bufferForPrint[25];

const float MAX_VALUE = 250;
const float MIN_SCALE = 25;
const float MAX_SCALE = 100;
// 12ma = 1023


float scaleValue(float value) {
    // assuming 0-255 in
    // want MAX_SCALE out
    return (value/MAX_VALUE)*MAX_SCALE + MIN_SCALE;
}

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
  print("hello.");
  setLevel(scaleValue(MAX_VALUE/2));
  wiggle();
  wifiSetup();
  print("connected.");
  wiggle();
}

void loop() {
  float result = 0;
  //Send an HTTP POST request every 10 minutes
  if (starting | (millis() - lastTime) > timerDelay) {
    clear();
    setLevel(scaleValue(50));
    delay(50);
    setLevel(scaleValue(0));
    //Check WiFi connection status
    if(isOnline()){
      print("online");
      starting = false;
      result = request();

      if(result > 0) {
        clear();
        sprintf(bufferForPrint, "AQI: %4.2f\n\0", result);
        print(bufferForPrint);
        Serial.println(result);
        setLevel(scaleValue(result));
      } else {
        setLevel(scaleValue(MAX_VALUE/2));
        wiggle();
      }
    }
    else {
      wiggle();
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
