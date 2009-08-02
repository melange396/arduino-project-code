//physical pixel: hsv

int hPin =  0;
int sPin =  1;
int vPin =  2;

int rPin =  9;
int gPin = 10;
int bPin = 11;

void setup() {
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);
}

void loop() {
  delay(10);
  
  float r, g, b,
        h, s, v,
        f, p, q, t;
  
  h = analogRead(hPin)/1024.0 * 360.0;
  s = analogRead(sPin)/1023.0;
  v = analogRead(vPin)/1023.0;

  f = h/60.0 - int(h/60.0);
  p = v*(1.0-s);
  q = v*(1.0-f*s);
  t = v*(1.0-(1.0-f)*s);

  switch (int(h/60.0) % 6) {
    case 0:
      r = v;
      g = t;
      b = p;
      break;
    case 1:
      r = q;
      g = v;
      b = p;
      break;
    case 2:
      r = p;
      g = v;
      b = t;
      break;
    case 3:
      r = p;
      g = q;
      b = v;
      break;
    case 4:
      r = t;
      g = p;
      b = v;
      break;
    case 5:
      r = v;
      g = p;
      b = q;
      break;
  }

  analogWrite(rPin, r*255.0);
  analogWrite(gPin, g*255.0);
  analogWrite(bPin, b*255.0);
}

