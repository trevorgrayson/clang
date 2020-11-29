#include "view.h"

#define FLASH_BTN 4


long count;
char buffer[25];

void setup() {
  count = 0;
  pinMode(FLASH_BTN, INPUT);
  viewSetup();
}


void loop() {
  sprintf(buffer, "hi %4ld", count);
  count++;
  //!digitalRead(FLASH_BTN); 
  topRightText(F(buffer));
  delay(50);
  if(count%250 == 0) {
    viewSetup();
    delay(100);
  }
}
