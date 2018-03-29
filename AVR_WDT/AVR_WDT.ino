#include <avr/wdt.h>
void enableWatchdog()
{
  cli();
  MCUSR &= ~(1<<WDRF);
  wdt_reset();
  WDTCR |= (1<<WDCE) | (1<<WDE);
  WDTCR = (~(1<<WDP1) & ~(1<<WDP2)) | ((1<<WDE) | (1<<WDIE) | (1<<WDP3) | (1<<WDP0));
  sei();
}

void disableWatchdog()
{
  cli();
  wdt_reset();
  MCUSR &= ~(1<<WDRF);
  WDTCR |= (1<<WDCE) | (1<<WDE);
  WDTCR = 0x00;
  sei();
}

ISR(WDT_vect)
{

}


void setup()
{
  disableWatchdog();
  enableWatchdog();
}

void loop()
{

}
