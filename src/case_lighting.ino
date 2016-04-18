// case lighting!
#include "../lib/hsi2rgbw.h"

#define REDPIN    5
#define GREENPIN  6
#define BLUEPIN   9
#define WHITEPIN  10

#define BUTTONPIN 3
#define LEDPIN    13

// #define BKNOB     1 // analog 1
// #define HKNOB     2 // analog 2

#define HKNOB 1
#define SKNOB 2
#define IKNOB 3

#define WHITE     0
#define COLOR     1
#define PULSE     2

#define FADESPEED 5
#define BSCALE    20 // fixed scalar for max brightness


volatile int buttonState = HIGH;  //unpressed
volatile int previousButtonState = HIGH;

int mode = 0;


void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  pinMode(WHITEPIN, OUTPUT);
  pinMode(BUTTONPIN,INPUT);
  pinMode(LEDPIN,OUTPUT);

  // initialize Timer2
  cli();          // disable global interrupts

  TCCR2A = 0;
  TCCR2B = 0;
  OCR2A =  150; //interrupt every 32ms with 256 prescaler
  TCCR2A |= (1<<WGM21); // turn on CTC mode
  TCCR2B |= (1<<CS22) | (1<<CS21); // 256 prescaler
  TIMSK2 |= (1 << OCIE2A); //enable timer compare interrupt

  sei();          // enable global interrupts
}


void loop() {

  float h, s, i;
  RgbwColor rgbw;

  h = (float) analogRead(HKNOB) / 2.84;
  s = (float) analogRead(SKNOB) / 1024.0;
  i = (float) analogRead(IKNOB) / 1024.0;

  hsi2rgbw(h,s,i,&rgbw);

  analogWrite(WHITEPIN,rgbw.w);
  analogWrite(REDPIN, rgbw.r);
  analogWrite(GREENPIN,rgbw.g);
  analogWrite(BLUEPIN,rgbw.b);



}

ISR(TIMER2_COMPA_vect)
{
    buttonState = digitalRead(BUTTONPIN);
    //button was pressed (went from high->low)
    if(buttonState == LOW && previousButtonState == HIGH){
      mode++;
      if(mode > 2){
        mode = 0;
      }
    }
    previousButtonState = buttonState;

}
