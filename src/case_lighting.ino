// case lighting!

#define REDPIN    5
#define GREENPIN  6
#define BLUEPIN   10
#define WHITEPIN  9

#define BUTTONPIN 3
#define LEDPIN    13

#define BKNOB     0
#define HKNOB     1

#define WHITE     0
#define RED       1
#define GREEN     2
#define BLUE      3

volatile int buttonState = HIGH;  //unpressed
volatile int previousButtonState = HIGH;

int color = 0;

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
  // int r, g, b, w;

  switch(color){
    case WHITE:
      analogWrite(REDPIN,0);
      analogWrite(GREENPIN,0);
      analogWrite(BLUEPIN,0);
      analogWrite(WHITEPIN, 5);
      break;
    case RED:
      analogWrite(GREENPIN,0);
      analogWrite(BLUEPIN,0);
      analogWrite(WHITEPIN, 0);
      analogWrite(REDPIN,5);
      break;
    case GREEN:
      analogWrite(REDPIN,0);
      analogWrite(BLUEPIN,0);
      analogWrite(WHITEPIN, 0);
      analogWrite(GREENPIN,5);
      break;
    case BLUE:
      analogWrite(REDPIN,0);
      analogWrite(GREENPIN,0);
      analogWrite(WHITEPIN, 0);
      analogWrite(BLUEPIN,5);
      break;
  }


}

ISR(TIMER2_COMPA_vect)
{
    buttonState = digitalRead(BUTTONPIN);
    //button was pressed (went from high->low)
    if(buttonState == LOW && previousButtonState == HIGH){
      color++;
      if(color > 3){
        color = 0;
      }
    }
    previousButtonState = buttonState;

}
