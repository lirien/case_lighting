// case lighting!

#define REDPIN    5
#define GREENPIN  6
#define BLUEPIN   9
#define WHITEPIN  10

#define BUTTONPIN 3
#define LEDPIN    13

#define BKNOB     1 // analog 1
#define HKNOB     2 // analog 2

#define WHITE     0
#define COLOR     1
#define PULSE     2

#define FADESPEED 5
#define BSCALE    10 // fixed scalar for max brightness


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
  int bval, hval, bscale;
  int rgbscale;
  int fr, fg, fb;

  bval = analogRead(BKNOB) / BSCALE;
  hval = analogRead(HKNOB);
  rgbscale = 168 / bval;


  switch(mode){
    case WHITE:
      analogWrite(REDPIN,0);
      analogWrite(GREENPIN,0);
      analogWrite(BLUEPIN,0);
      analogWrite(WHITEPIN, bval);
      break;
    case COLOR:

      analogWrite(WHITEPIN,0);
      //off
      if(bval == 0){
        analogWrite(REDPIN,0);
        analogWrite(GREENPIN,0);
        analogWrite(BLUEPIN,0);
      }

      //blue to violet
      else if(hval < 172){
        analogWrite(GREENPIN,0);
        analogWrite(BLUEPIN, bval);
        // r = hval;
        analogWrite(REDPIN, hval / rgbscale);
      }

      //violet to red
      else if(hval < 340){
        analogWrite(GREENPIN,0);
        analogWrite(REDPIN, bval);
        //b = 85 - hval;
        analogWrite(BLUEPIN, (340 - hval) / rgbscale);
      }

      //red to yellow
      else if(hval < 512){
        analogWrite(BLUEPIN,0);
        analogWrite(REDPIN, bval);
        //g = hval - 85
        analogWrite(GREENPIN, (hval - 340) / rgbscale);
      }

      //yellow to green
      else if(hval < 680){
        analogWrite(BLUEPIN,0);
        analogWrite(GREENPIN, bval);
        //r = 170 - hval;
        analogWrite(REDPIN, (680 - hval) / rgbscale);
      }

      //green to teal
      else if(hval < 852){
        analogWrite(REDPIN,0);
        analogWrite(GREENPIN, bval);
        //b = hval - 170
        analogWrite(BLUEPIN, (hval - 680) / rgbscale);
      }

      //teal to blue
      else{
        analogWrite(REDPIN,0);
        analogWrite(BLUEPIN, bval);
        //g = 255 - hval;
        analogWrite(GREENPIN, (1027 - hval) / rgbscale);
      }
      break;

    case PULSE:
    // fade from blue to violet
    for (fr = 0; fr < 256; fr++) {
      analogWrite(REDPIN, fr / BSCALE);
      delay(FADESPEED);
      if(mode != PULSE) break;
    }
    // fade from violet to red
    for (fb = 255; fb > 0; fb--) {
      analogWrite(BLUEPIN, fb / BSCALE);
      delay(FADESPEED);
      if(mode != PULSE) break;
    }
    // fade from red to yellow
    for (fg = 0; fg < 256; fg++) {
      analogWrite(GREENPIN, fg / BSCALE);
      delay(FADESPEED);
      if(mode != PULSE) break;
    }
    // fade from yellow to green
    for (fr = 255; fr > 0; fr--) {
      analogWrite(REDPIN, fr / BSCALE);
      delay(FADESPEED);
      if(mode != PULSE) break;
    }
    // fade from green to teal
    for (fb = 0; fb < 256; fb++) {
      analogWrite(BLUEPIN, fb / BSCALE);
      delay(FADESPEED);
      if(mode != PULSE) break;
    }
    // fade from teal to blue
    for (fg = 255; fg > 0; fg--) {
      analogWrite(GREENPIN, fg / BSCALE);
      delay(FADESPEED);
      if(mode != PULSE) break;
    }
      break;
  }


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
