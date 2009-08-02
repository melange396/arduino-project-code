
// lights controlled by serial

int  pins[]   = {   9,  11,  13 };
char keys[]   = { 'a', 's', 'd' };

const int numPins = sizeof(pins)/sizeof(int);
int states[numPins];

void setup() {
  Serial.begin(9600);
  for (int i=0 ; i<numPins ; i++) {
    pinMode(pins[i], OUTPUT);
    states[i] = LOW;
  }
}

void loop() {
  if (Serial.available() > 0) {
    char in = char(Serial.read());
    for (int i=0 ; i<numPins ; i++) {
      if (in==keys[i]) {
        states[i] = (states[i]==HIGH) ? LOW : HIGH;
        digitalWrite(pins[i], states[i]);
      }
    }
  }
  delay(20);
}
