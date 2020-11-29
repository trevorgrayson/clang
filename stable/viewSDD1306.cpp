#include <stdio.h>
#include <math.h>

#include "ssd1306.h"
#include "nano_gfx.h"


void viewSetup() {
  Serial.begin(9600);
  ssd1306_setFixedFont(ssd1306xled_font6x8);
  ssd1306_128x32_i2c_init();
  // composite_video_128x64_mono_init(); // Use this line for ESP32 with Composite video support

  ssd1306_clearScreen();
  //ssd1306_createMenu( &menu, menuItems, sizeof(menuItems) / sizeof(char *) );
  //ssd1306_showMenu( &menu );
  ssd1306_printFixed(30,  0, "Normal text", STYLE_NORMAL);
  //ssd1306_printFixed(0, 16, "Bold text", STYLE_BOLD);
  //ssd1306_printFixed(0, 24, "Italic text", STYLE_ITALIC);
  ssd1306_positiveMode();
  ssd1306_clearScreen();
  Serial.println(F("OK"));
}

void clear() { ssd1306_clearScreen(); }
void viewRender() { }
  
void print() {
  //ssd1306_clearScreen();
  //ssd1306_printFixed(30,  10, *buffer, STYLE_NORMAL);
  //ssd1306_positiveMode();
}

void topRightText(char *buffer) {
  //ssd1306_clearScreen();
  ssd1306_printFixed(80, 0, buffer, STYLE_NORMAL);
  //ssd1306_positiveMode();
}
