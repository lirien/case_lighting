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
#define SAT       17

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
  int r, g, b, w;

  bval = analogRead(BKNOB) / 10;
  hval = analogRead(HKNOB);


  switch(mode){
    case WHITE:
      analogWrite(REDPIN,0);
      analogWrite(GREENPIN,0);
      analogWrite(BLUEPIN,0);
      analogWrite(WHITEPIN, bval);
      break;
    case COLOR:
      analogWrite(REDPIN,0);
      analogWrite(GREENPIN,30);
      analogWrite(BLUEPIN,30);
      analogWrite(WHITEPIN, 0);
      break;
    case PULSE:
    // fade from blue to violet
    for (r = 0; r < 256; r++) {
      analogWrite(REDPIN, r / 10);
      delay(FADESPEED);
      if(mode != PULSE) break;
    }
    // fade from violet to red
    for (b = 255; b > 0; b--) {
      analogWrite(BLUEPIN, b / 10);
      delay(FADESPEED);
      if(mode != PULSE) break;
    }
    // fade from red to yellow
    for (g = 0; g < 256; g++) {
      analogWrite(GREENPIN, g / 10);
      delay(FADESPEED);
      if(mode != PULSE) break;
    }
    // fade from yellow to green
    for (r = 255; r > 0; r--) {
      analogWrite(REDPIN, r / 10);
      delay(FADESPEED);
      if(mode != PULSE) break;
    }
    // fade from green to teal
    for (b = 0; b < 256; b++) {
      analogWrite(BLUEPIN, b / 10);
      delay(FADESPEED);
      if(mode != PULSE) break;
    }
    // fade from teal to blue
    for (g = 255; g > 0; g--) {
      analogWrite(GREENPIN, g / 10);
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
