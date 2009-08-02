// cylon

int pins[]  = {9, 11, 13};
int numPins = sizeof(pins)/sizeof(int);
int period  = 50;

void setup() {  
  for (int i=0 ; i<numPins ; i++) {
    pinMode(pins[i], OUTPUT);
  }
}

void loop() {
  for (int i=0 ; i<numPins ; i++) {
    flash(pins[i], period);
  }
  for (int i=numPins-1 ; i>=0 ; i--) {
    flash(pins[i], period);
  }
}

void flash(int pin, int length) {
  digitalWrite(pin, HIGH);
  delay(length);
  digitalWrite(pin, LOW);
}
