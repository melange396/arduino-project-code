// light dimmer controlled by serial

int  pins[]   = {   9,  11 };
char keys[]   = { 'a', 's' };
int  inc      = 32;

const int numPins = sizeof(pins)/sizeof(int);
int states[numPins];

void setup() {
  Serial.begin(9600);
  for (int i=0 ; i<numPins ; i++) {
    pinMode(pins[i], OUTPUT);
    states[i] = 0;
  }
}

void loop() {
  if (Serial.available() > 0) {
    char in = char(Serial.read());
    for (int i=0 ; i<numPins ; i++) {
      if (in==keys[i]) {
        states[i] = (states[i] + inc) % 256;
        analogWrite(pins[i], states[i]);
        Serial.print("state change {pin:");
        Serial.print(pins[i]);
        Serial.print(", value:");
        Serial.print(states[i]);
        Serial.println("}");
      }
    }
  }
  delay(20);
}
