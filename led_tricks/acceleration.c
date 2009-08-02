// acceleration

int   period     = 500;
float multiplier = 0.999;

int   pins[]     = {9, 11, 13};
int   numPins    = sizeof(pins)/sizeof(int);

void setup() {  
  for (int i=0 ; i<numPins ; i++) {
    pinMode(pins[i], OUTPUT);
  }
}

void loop() {
  for (int i=0 ; i<numPins ; i++) {
    flash(pins[i], period);
    period *= multiplier;
  }
}

void flash(int pin, int length) {
  digitalWrite(pin, HIGH);
  delay(length);
  digitalWrite(pin, LOW);
}
