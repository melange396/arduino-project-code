
// pulser

int increment = 1;
int period    = 1;
int pins[]    = {9,  11};
const int numPins = sizeof(pins)/sizeof(int);
int state;

void setup() {
  Serial.begin(9600);
  for (int i=0 ; i<numPins ; i++) {
    pinMode(pins[i], OUTPUT);
  }
  state = 0;
}

void loop() {
  while (0 <= state && state < 256) {
    for (int i=0 ; i<numPins ; i++)
      analogWrite(pins[i], state);
    state += increment;
    delay(period);
  }
  increment *= -1;
  state     += increment;
}
