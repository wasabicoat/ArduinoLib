#include <Arduino.h>
#include <avr/wdt.h>
/*
  watchdog timer example code.

  flashes LED three times quickly on boot up. Then goes thru a loop delaying
  an additional 250ms on each iteration. The LED is on during each delay.
  Once the delay is long enough, the WDT will reboot the MCU.
*/

const int onboardLED = 13;
unsigned long loopCount = 0;

void setup() {

    Serial.begin(9600);
    Serial.println("Reset");
    int k;
    loopCount = 0;
    wdt_disable();

    delay(2L * 1000L);
    wdt_enable(WDTO_4S);

    pinMode(onboardLED, OUTPUT);

    for (k = 1; k <= 3; k = k + 1) {
        digitalWrite(onboardLED, HIGH);
        delay(250L);
        digitalWrite(onboardLED, LOW);
        delay(250L);
    }
    delay(750L);
}

void loop() {

    int k;
    loopCount += 1;
//    wdt_reset();
    Serial.print("Loop Count : "); 
    Serial.println(loopCount); 
    delay(1000);
}
