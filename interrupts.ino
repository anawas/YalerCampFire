/******************************************
 ** interrupts
 **
 ** Initializes a timer interrupt to compare mode
 ** and provides the function called when interrupted.
 ********************************************/

// this function is called by the timer interrupt every 0.6 ms.
// The counter randOn is decreased at each call. 
// Because it's set to a random value between 30 and 50
// the LEDs change state each 18 to 30 ms, which gives a
// reasonable flicker.
ISR(TIMER1_COMPA_vect)
{
  --randOn;
  if (randOn == 0) {
    if (ledState == FIRE_OFF) {
      analogWrite(randomLED, fireIntensity);
      ledState = FIRE_ON;
    }
    else {
      digitalWrite(randomLED, HIGH);
      ledState = FIRE_OFF;
    } 
    //digitalWrite(randomLED, !digitalRead(randomLED));
    randOn = random(30, 50);
    randomLED = random(1,3) * 3;
   }
}

/** This code is taken from 
 * http://www.engblaze.com/microcontroller-tutorial-avr-and-arduino-timer-interrupts/
 **/
void initInterrupt(){
  // initialize Timer1
  cli();          // disable global interrupts
  TCCR1A = 0;     // set entire TCCR1A register to 0
  TCCR1B = 0;     // same for TCCR1B
 
  // set compare match register to desired timer count:
  // OCR1A = 15624; // about 1 sec.
  
  OCR1A = 10;  // want the LED to flicker --> 0.6 ms. Don't worry
               // this value is multiplied randomly by a factor 30 - 50
               // (see variable randOn)
  
  // turn on CTC mode:
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler:
  TCCR1B |= (1 << CS10);
  TCCR1B |= (1 << CS12);
  // enable timer compare interrupt:
  TIMSK1 |= (1 << OCIE1A);
  sei();          // enable global interrupts
 }

