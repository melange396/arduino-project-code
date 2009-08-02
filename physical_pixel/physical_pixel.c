// physical pixel

char pinColors[] = { 'r', 'g', 'b' };
int  outPins[]   = {   9,  10,  11 };
int  inPins[]    = {   0,   1,   2 };
int  pinBounds[] = { 255, 255, 100 };
const int numPins = sizeof(outPins)/sizeof(int);

void setup() {
  for (int i=0 ; i<numPins ; i++)
    pinMode(outPins[i], OUTPUT);
}

void loop() {
  delay(10);
  for (int i=0 ; i<numPins ; i++)
    analogWrite(outPins[i], map(analogRead(inPins[i]), 0, 1023, 0, pinBounds[i]));
}
