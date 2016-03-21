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



volatile int buttonState = HIGH;  //unpressed
volatile int previousButtonState = HIGH;

int mode = 0;
int hval, bval = 0;

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
  int r, g, b, w;

  switch(mode){
    case WHITE:
      analogWrite(REDPIN,0);
      analogWrite(GREENPIN,0);
      analogWrite(BLUEPIN,0);
      analogWrite(WHITEPIN, bval);
      break;
    case COLOR:
      analogWrite(GREENPIN,0);
      analogWrite(BLUEPIN,0);
      analogWrite(WHITEPIN, 0);
      analogWrite(REDPIN,5);
      break;
    case PULSE:
    // fade from blue to violet
    for (r = 0; r < 256; r++) {
      analogWrite(REDPIN, r);
      delay(FADESPEED);
    }
    // fade from violet to red
    for (b = 255; b > 0; b--) {
      analogWrite(BLUEPIN, b);
      delay(FADESPEED);
    }
    // fade from red to yellow
    for (g = 0; g < 256; g++) {
      analogWrite(GREENPIN, g);
      delay(FADESPEED);
    }
    // fade from yellow to green
    for (r = 255; r > 0; r--) {
      analogWrite(REDPIN, r);
      delay(FADESPEED);
    }
    // fade from green to teal
    for (b = 0; b < 256; b++) {
      analogWrite(BLUEPIN, b);
      delay(FADESPEED);
    }
    // fade from teal to blue
    for (g = 255; g > 0; g--) {
      analogWrite(GREENPIN, g);
      delay(FADESPEED);
    }
      break;
  }

  hval = analogRead(HKNOB);
  bval = analogRead(BKNOB) / 10;


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
