/**************************
 ** RGB LED as a candle! **
 **************************/

///TODO: ? seperate alphas for various parameters (h,s,v,d)
///TODO: ? speedp --
///         -reduce float instances to integer division
///         -maybe cut some useless crap like hsv bounds checking with #ifdef
///TODO: ?? change alpha fn and usage?

// common anode rgb leds have the 4th pin tied to +5v; the elements
// turn ON when their control pins are set LOW, and turn OFF when
// their control pins are set HIGH -- unlike what you might expect...
// setting this constant TRUE compensates for that behavior.
const boolean commonAnode = true;

const int rPin = 9;
const int gPin = 10;
const int bPin = 11;
const int sPin = 13;
const int uPin = 0;  // unconnected analog pin, provides noise for random seed

const float hMin = 30;   // hue
const float hMax = 40;   //   (30, 40) confines this to yellowish orange
const float sMin = 0.9;  // saturation
const float sMax = 1;    //   any lower than (.9, 1) and it looks too white
const float vMin = 0.05; // value
const float vMax = 1;    //   could easily be (0, 1), sets the 'depth' of the flicker
const float dMin = 10;   // delay between led value changes
const float dMax = 100;

const float a = 0.4; // ratio for doing transitions with linear products to prevent wild swings in appearance
void alpha(float *x, float newVal) { *x = (*x)*a + newVal*(1-a); } // performs linear product.  be sure to call this with the first argument referenced! [ie, alpha(&blah, 4)]
void alpha(float *x, float mini, float maxi) { alpha(x, rnd(mini, maxi)); }

// some big number for getting good randomness resolution.   2^14 fits in max signed int and should be nicely represented as a float...  i think?
const float BIGNUM = 1 << 14;
// random number, fractional and inclusive
float rnd(float maximum) { return maximum * random(BIGNUM+1)/BIGNUM; }
// randome number from zero to one, inclusive
float rnd() { return rnd(1); }
// random number, fractional and inclusive, with minimum
float rnd(float minimum, float maximum) { return minimum + rnd(maximum-minimum); }

float h, s, v, d;
unsigned long t;

void resetCandle() {
  h = (hMin+hMax)/2;
  s = sMax;
  v = vMin;
  d = dMin;
  t = 0;
  digitalWrite(sPin, HIGH);
  delay(333);
  digitalWrite(sPin, LOW);
}

void setup() {
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);
  pinMode(sPin, OUTPUT);
  randomSeed(analogRead(uPin));
  resetCandle();
}

void loop() {
  unsigned long now = millis();
  if (now >= t+long(d) || now <= d) { // if we are past the delay, or the timer has rolled over...
    setLedsHSV(h, s, v);
    alpha(&h, hMin, hMax);
    alpha(&s, sMin, sMax);
    alpha(&v, vMin, vMax);
    alpha(&d, dMin, dMax);
    t = now;
  }
  delay(1);
}

void setLedsHSV(float h, float s, float v){
  // check h in [0, 360), else do modulus:
  if (h >= 360) h -= 360*int(h/360);
  // check s & v in [0, 1], else truncate:
  if (s < 0) s *= -1;
  if (v < 0) v *= -1;
  if (s > 1) s -= int(s);
  if (v > 1) v -= int(v);

  float r, g, b,
        f, p, q, t;
        
  f = h/60 - int(h/60);
  p = v*(1-s);
  q = v*(1-f*s);
  t = v*(1-(1-f)*s);

  switch (int(h/60) % 6) {
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

  if (commonAnode) {
    r = 1-r;
    g = 1-g;
    b = 1-b;
  }
  
  analogWrite(rPin, r*255);
  analogWrite(gPin, g*255);
  analogWrite(bPin, b*255);
}
