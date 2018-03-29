const byte ledPin = 13;
const byte intertuptPin = 2;
volatile byte state = LOW;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(intertuptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(intertuptPin), blink, CHANGE);
}

void loop() {
  digitalWrite(ledPin, state);
}

void blink() {
  state = !state;
}
