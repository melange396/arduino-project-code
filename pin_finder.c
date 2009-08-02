// pin finder

int startPin = 9;
int numPins  = 3;
int pinStep  = 2;

void setup() {  
  for (int i=0 ; i<numPins ; i++) {
    pinMode(startPin+(i*pinStep), OUTPUT);
  }
}

void loop() {
  for (int i=0 ; i<numPins ; i++) {
    for (int j=0 ; j<i+1 ; j++) {
      int thisPin = startPin+(i*pinStep);
      digitalWrite(thisPin, HIGH);
      delay(150);
      digitalWrite(thisPin, LOW);
      delay(150);
    }
    delay(300);
  }
}
