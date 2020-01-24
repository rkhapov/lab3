#include <LedControl.h>
#include <Servo.h>
#include "button.h"

Servo servo;

const int displaysCount = 1;
const int dataPin = 12;
const int clkPin = 10;
const int csPin = 11;

LedControl lc = LedControl(dataPin, clkPin, csPin, displaysCount);

int power = 0;

const int buttonPin = 9;
const int strikePin = 8;
const int serv_pin = 7;

Button button = Button(buttonPin);
Button strikeButton = Button(strikePin);

void setup() {
  Serial.begin(115200);
  Serial.println("Started!");
  
  for (int i = 0; i < displaysCount; i++) {
    lc.shutdown(i, false);
    lc.setIntensity(i, 50);
    lc.clearDisplay(i);
  }

   servo.attach(serv_pin);
   servo.write(0);
}

void loop() {
  if (button.wasPressed()) {
    Serial.print("power increased to ");
    Serial.print((power + 1) % 9);
    Serial.println();
    power = (power + 1) % 9;
  }

  if (strikeButton.wasPressed()) {
    Serial.println("strike!");
    do_strike(); 
    servo.write(0);
  }

 
  
  drawPower();
}


void do_strike() {
  for(int i=0; i<=90; i++){
    servo.write(i);
    delay(18 / (1 + power));
  }    
}


void drawPower() {
  lc.clearDisplay(0);
  
  for (int y = 0; y < power; y++) {
    for (int x = 0; x < 8; x++) {
      lc.setLed(0, y, x, 1);
    }
  }
}
