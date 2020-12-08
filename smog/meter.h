#include <Arduino.h>


const int meter = 12;
float level = 0;
int last = 0;


void meterSetup() {
  pinMode(meter, OUTPUT);  // sets the pin as output
  //analogWriteRange(2050);

  //analogWrite(meter, 155);
  //delay(100);
  //analogWrite(meter, 0);
  //delay(100);
}

void setLevel(float l) {
  level = l;
  if(level > last) {
     for(int dutyCycle = last; dutyCycle <= level; dutyCycle++){
       // changing the LED brightness with PWM
       analogWrite(meter, dutyCycle);
       delay(50);
     }
  } else {
     for(int dutyCycle = last; dutyCycle >= level; dutyCycle--){
       // changing the LED brightness with PWM
       analogWrite(meter, dutyCycle);
       delay(50);
     }
  }

  last = level;
}

void wiggle() {
//  analogWrite(meter, level - 50);
//  delay(50);
  analogWrite(meter, level - 25);
  delay(50);
  analogWrite(meter, level + 25);
  delay(50);
  analogWrite(meter, level);
  delay(50);
}
