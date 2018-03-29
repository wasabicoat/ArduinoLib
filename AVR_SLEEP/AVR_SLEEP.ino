// ATtiny85 sleep mode, wake on pin change interrupt demo
// Author: Nick Gammon
// Date: 12 October 2013

// ATMEL ATTINY 25/45/85 / ARDUINO
//
//                  +-\/-+
// Ain0 (D 5) PB5  1|    |8  Vcc
// Ain3 (D 3) PB3  2|    |7  PB2 (D 2) Ain1
// Ain2 (D 4) PB4  3|    |6  PB1 (D 1) pwm1
//            GND  4|    |5  PB0 (D 0) pwm0
//                  +----+

#include <avr/sleep.h>    // Sleep Modes
#include <avr/power.h>    // Power management

const byte LED = 0;  // pin 2 / PCINT4
const byte SWITCH = 4; // pin 3

ISR (PCINT0_vect) 
{     
  digitalWrite (LED, HIGH);
  delay (500); 
  digitalWrite (LED, LOW);
  delay (500); 
  digitalWrite (LED, HIGH);
  delay (500); 
  digitalWrite (LED, LOW);
  delay (500); 
}
 
void setup ()
{
  pinMode (LED, OUTPUT);
  pinMode (SWITCH, INPUT);
  digitalWrite (SWITCH, HIGH);  // internal pull-up
  
  // pin change interrupt (example for D3)
  PCMSK  |= bit (PCINT4);  // want pin D3 / pin 2
  GIFR   |= bit (PCIF);    // clear any outstanding interrupts
  GIMSK  |= bit (PCIE);    // enable pin change interrupts 

}  // end of setup

void loop ()
{
  digitalWrite (LED, HIGH);
  delay (500); 
  digitalWrite (LED, LOW);
  delay (500); 
  goToSleep ();
}  // end of loop
  
  
void goToSleep ()
{
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  ADCSRA = 0;            // turn off ADC
  power_all_disable ();  // power off ADC, Timer 0 and 1, serial interface
  sleep_enable();
  sleep_cpu();                             
  sleep_disable();   
  power_all_enable();    // power everything back on
}  // end of goToSleep
