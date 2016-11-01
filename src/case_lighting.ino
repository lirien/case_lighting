#include "../lib/hsi2rgbw.h"

#define REDPIN    5
#define GREENPIN  6
#define BLUEPIN   9
#define WHITEPIN  10

#define BUTTONPIN 3
#define LEDPIN    13

#define HKNOB 1
#define SKNOB 2
#define IKNOB 3

void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  pinMode(WHITEPIN, OUTPUT);
  pinMode(LEDPIN, OUTPUT);
}

void loop() {
  float h, s, i;
  RgbwColor rgbw;

  h = (float) analogRead(HKNOB) / 2.84;
  s = (float) analogRead(SKNOB) / 1024.0;
  i = (float) analogRead(IKNOB) / 1024.0;

  hsi2rgbw(h, s, i, &rgbw);

  analogWrite(WHITEPIN,rgbw.w);
  analogWrite(REDPIN, rgbw.r);
  analogWrite(GREENPIN, rgbw.g);
  analogWrite(BLUEPIN, rgbw.b);
}
