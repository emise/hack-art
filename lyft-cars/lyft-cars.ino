#include <Bounce2.h>

/* 
 *  Logic for backlighting two Lyft cars
 */

const int DEBOUNCE_INTERVAL = 5;

const int carRedPin = 3;
const int carGreenPin = 5;
const int carBluePin = 6;

const int carTrigger = 4;
Bounce debouncer = Bounce();

int carTriggerVal = 0;

void setup() {
  pinMode(carRedPin, OUTPUT);
  pinMode(carGreenPin, OUTPUT);
  pinMode(carBluePin, OUTPUT);

  pinMode(carTrigger, INPUT);
  debouncer.attach(carTrigger);
  debouncer.interval(DEBOUNCE_INTERVAL);
}

void setColor(int r, int g, int b) {
  analogWrite(carRedPin, r);
  analogWrite(carGreenPin, g);            
  analogWrite(carBluePin, b);
}

void clearColor() {
  setColor(0, 0, 0);
}

void loop() {
  debouncer.update();
  carTriggerVal = debouncer.read();

  if (carTriggerVal == HIGH) {
    setColor(255, 0, 191); // pink
  } else {
    clearColor();
  }
  delay(10);
}

