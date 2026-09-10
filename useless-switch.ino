#include <Servo.h>

Servo servo;

// Pins
const int switchPin = 2;
const int servoPin = 9;

// Servo positions
const int HOME = 20;
const int PUSH = 110;

void setup() {
  pinMode(switchPin, INPUT_PULLUP);

  servo.attach(servoPin);
  servo.write(HOME);

  randomSeed(analogRead(A0));
}

void loop() {

  // Switch is turned ON
  if (digitalRead(switchPin) == LOW) {

    delay(300);

    // Random attitude
    int mood = random(1, 6);

    switch (mood) {

      case 1:
        // Immediately switch it off
        pushSwitch();
        break;

      case 2:
        // Wait before reacting
        delay(1200);
        pushSwitch();
        break;

      case 3:
        // Pretend to do something
        servo.write(70);
        delay(300);
        servo.write(HOME);
        delay(500);
        pushSwitch();
        break;

      case 4:
        // Multiple movements
        servo.write(70);
        delay(250);
        servo.write(HOME);
        delay(250);
        servo.write(70);
        delay(250);
        servo.write(HOME);
        delay(400);
        pushSwitch();
        break;

      case 5:
        // Long dramatic pause
        delay(2500);
        pushSwitch();
        break;
    }

    // Wait until the user turns the switch ON again
    while (digitalRead(switchPin) == LOW) {
      delay(50);
    }

    delay(500);
  }
}

void pushSwitch() {

  // Move toward switch
  servo.write(PUSH);
  delay(500);

  // Keep pressure briefly
  delay(300);

  // Return inside
  servo.write(HOME);
  delay(500);
}
