// color swirl! connect an RGB LED to the PWM pins as indicated
// in the #defines
// public domain, enjoy!

#define REDPIN    5
#define GREENPIN  6
#define BLUEPIN   3
#define WHITEPIN  9

#define BUTTONPIN 8
#define LEDPIN    13

#define BKNOB     0
#define HKNOB     1

#define FADESPEED 5     // make this higher to slow down

int buttonState = 0;

void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  pinMode(WHITEPIN, OUTPUT);
  pinMode(BUTTONPIN,INPUT);
  pinMode(LEDPIN,OUTPUT);
}


void loop() {
  // int r, g, b, w;

  analogWrite(BLUEPIN,0);
  analogWrite(WHITEPIN, 5);
  delay(1000);
  analogWrite(WHITEPIN, 0);
  analogWrite(REDPIN,5);
  delay(1000);
  analogWrite(REDPIN,0);
  analogWrite(GREENPIN,5);
  delay(1000);
  analogWrite(GREENPIN,0);
  analogWrite(BLUEPIN,5);
  delay(1000);


  // fade from blue to violet
  // for (r = 0; r < 256; r++) {
  //   analogWrite(REDPIN, r);
  //   delay(FADESPEED);
  // }
  // // fade from violet to red
  // for (b = 255; b > 0; b--) {
  //   analogWrite(BLUEPIN, b);
  //   delay(FADESPEED);
  // }
  // // fade from red to yellow
  // for (g = 0; g < 256; g++) {
  //   analogWrite(GREENPIN, g);
  //   delay(FADESPEED);
  // }
  // // fade from yellow to green
  // for (r = 255; r > 0; r--) {
  //   analogWrite(REDPIN, r);
  //   delay(FADESPEED);
  // }
  // // fade from green to teal
  // for (b = 0; b < 256; b++) {
  //   analogWrite(BLUEPIN, b);
  //   delay(FADESPEED);
  // }
  // // fade from teal to blue
  // for (g = 255; g > 0; g--) {
  //   analogWrite(GREENPIN, g);
  //   delay(FADESPEED);
  // }
}
