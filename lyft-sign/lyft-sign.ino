#include <Bounce2.h>

/*
 * Master Arduino logic
 * Controls the skyline and landmark LEDs
 * Outputs a signal to control Lyft sign via relay switch (on/off)
 * Outputs a signal to control car lights (via another Arduino)
 * Behavior:
 * any 1 button pressed: Lyft logo lights up
 * any 2 buttons pressed: Lyft logo, cars
 * any 3 buttons pressed: Lyft logo, cars, skyline
 * all 4 buttons pressed: Lyft logo, cars, skyline cycles through rainbow color,
 * and foreground landmarks light up
 */

const int DEBOUNCE_TIME = 5;
const int CYCLE_DELAY = 50;

const int btn1 = A2;
const int btn2 = A3;
const int btn3 = A4;
const int btn4 = A5;

int btn1Val = 0;
int btn2Val = 0;
int btn3Val = 0;
int btn4Val = 0;

// prevent side effects of buttons being pressed too quickly
Bounce debouncer1 = Bounce();
Bounce debouncer2 = Bounce();
Bounce debouncer3 = Bounce();
Bounce debouncer4 = Bounce();

int buttonsPressed = 0;

const int skylineRedPin = 3;
const int skylineGreenPin = 5;
const int skylineBluePin = 6;

const int landmarksRedPin = 9;
const int landmarksGreenPin = 10;
const int landmarksBluePin = 11;

const int lyftLogoPin = 12;
const int carPin = 4;

// for color cycling with fake interrupts
int R = 0;
int G = 0;
int B = 256;
int cycle_incrementer = 1;

void setup() {
  pinMode(btn1, INPUT_PULLUP);
  debouncer1.attach(btn1);
  debouncer1.interval(DEBOUNCE_TIME);
  pinMode(btn2, INPUT_PULLUP);
  debouncer2.attach(btn2);
  debouncer2.interval(DEBOUNCE_TIME);
  pinMode(btn3, INPUT_PULLUP);
  debouncer3.attach(btn3);
  debouncer3.interval(DEBOUNCE_TIME);
  pinMode(btn4, INPUT_PULLUP);
  debouncer4.attach(btn4);
  debouncer4.interval(DEBOUNCE_TIME);

  pinMode(skylineRedPin, OUTPUT);
  pinMode(skylineGreenPin, OUTPUT);
  pinMode(skylineBluePin, OUTPUT);

  pinMode(landmarksRedPin, OUTPUT);
  pinMode(landmarksGreenPin, OUTPUT);
  pinMode(landmarksBluePin, OUTPUT);

  pinMode(lyftLogoPin, OUTPUT);
  pinMode(carPin, OUTPUT);
  clearLights();
}

void setColor(String pin, int r, int g, int b) {
  if (pin == "skyline") {
    analogWrite(skylineRedPin, r);
    analogWrite(skylineGreenPin, g);
    analogWrite(skylineBluePin, b);
  } else if (pin == "landmarks") {
    analogWrite(landmarksRedPin, r);
    analogWrite(landmarksGreenPin, g);
    analogWrite(landmarksBluePin, b);
  }
}

void clearLights() {
  digitalWrite(lyftLogoPin, LOW);
  digitalWrite(carPin, LOW);

  setColor("skyline", 0, 0, 0);
  setColor("landmarks", 0, 0, 0);
}

// cycle rainbow colors!
// interrupt every 50ms to check number of buttons pressed
void cycleColors() {
  int interval;
  // fade from blue to violet
  if (R < 256 && G == 0 && B == 256) {
    while (cycle_incrementer <= 25) {
      interval = cycle_incrementer * CYCLE_DELAY;
      while (R < interval) {
        analogWrite(skylineRedPin, R);
        delay(1);
        R++;
      }
      cycle_incrementer++;
      return;
    }
  }
  // fade from violet to red
  if (R == 256 && G == 0 && B > 0) {
    while (cycle_incrementer > 0) {
      interval = cycle_incrementer * CYCLE_DELAY;
      while (B > interval) {
        analogWrite(skylineBluePin, B);
        delay(1);
        B--;
      }
      cycle_incrementer--;
      return;
    }
  }

  // fade from red to yellow
  if (R == 256 && G < 256 && B == 0) {
    while (cycle_incrementer <= 25) {
      interval = cycle_incrementer * CYCLE_DELAY;
      while (G < interval) {
        analogWrite(skylineGreenPin, G);
        delay(1);
        G++;
      }
      cycle_incrementer--;
      return;
    }
  }

  // fade from yellow to green
  if (R > 0 && G == 256 && B == 0) {
    while (cycle_incrementer > 0) {
      interval = cycle_incrementer * CYCLE_DELAY;
      while (R > interval) {
        analogWrite(skylineRedPin, R);
        delay(1);
        R--;
      }
      cycle_incrementer--;
      return;
    }
  }

  // fade from green to teal
  if (R == 0 && G == 256 && B < 256) {
    while (cycle_incrementer <= 25) {
      interval = cycle_incrementer * CYCLE_DELAY;
      while (B < interval) {
        analogWrite(skylineBluePin, B);
        delay(1);
        B++;
      }
      cycle_incrementer--;
      return;
    }
  }

  // fade from teal to blue
  if (R == 0 && G > 0 && B == 256) {
    while (cycle_incrementer > 0) {
      interval = cycle_incrementer * CYCLE_DELAY;
      while (G > interval) {
        analogWrite(skylineGreenPin, G);
        delay(1);
        G--;
      }
      cycle_incrementer--;
      return;
    }
  }
}

void lyftLogo() {
  digitalWrite(lyftLogoPin, HIGH);
}

void cars() {
  digitalWrite(carPin, HIGH);
}

void skyline() {
  setColor("skyline", 128, 0, 128); // purple
}

void landmarks() {
  setColor("landmarks", 0, 0, 255); // blue
}

/* Lyft logo */
void turnOnOne() {
  lyftLogo();
}

/* Lyft logo and cars */
void turnOnTwo() {
  lyftLogo();
  cars();
}

/* Lyft logo, cars and skyline */
void turnOnThree() {
  lyftLogo();
  cars();
  skyline();
}

/* Lyft logo, cars, skyline, special buildings */
void turnOnFour() {
  lyftLogo();
  cars();
  skyline();
  landmarks();
  cycleColors();
}

void loop() {
  debouncer1.update();
  debouncer2.update();
  debouncer3.update();
  debouncer4.update();
  btn1Val = debouncer1.read();
  btn2Val = debouncer2.read();
  btn3Val = debouncer3.read();
  btn4Val = debouncer4.read();

  buttonsPressed = 4 - (btn1Val + btn2Val + btn3Val + btn4Val);
  switch (buttonsPressed) {
    case 0:
      clearLights();
      delay(CYCLE_DELAY);
      break;
    case 1:
      turnOnOne();
      delay(CYCLE_DELAY);
      break;
    case 2:
      turnOnTwo();
      delay(CYCLE_DELAY);
      break;
    case 3:
      turnOnThree();
      delay(CYCLE_DELAY);
      break;
    case 4:
      turnOnFour();
      break;
    default:
      clearLights();
      delay(CYCLE_DELAY);
      break;
  }
}
