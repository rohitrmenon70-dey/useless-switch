#include <Servo.h>

// ============================================================
// BOARD: Arduino Nano
//
// Servo:
// Orange/yellow wire -> D9
// Red wire            -> 5V
// Brown/black wire    -> GND
//
// Switch:
// Connect switch between D2 and D3
//
// Built-in LED:
// D13
// ============================================================

#define SERVO_PIN 9

// Connect the switch across pins 2 and 3
#define SWITCH_PIN 2
#define SWITCH_OUT 3

// Built-in LED
#define LED_BUILTIN 13

// Servo range of motion
// Starting/resting position
// Ending/hitting-the-switch position
#define POS_START 180
#define POS_END 45

Servo myservo;

int switchState;
int pos = POS_START;
int target = POS_START;
int seq = 0;
int rapidCount = -1;
unsigned long lastInput = 0;
bool goRandom;


// ============================================================
// SETUP
// ============================================================

void setup() {

  pinMode(SWITCH_PIN, INPUT_PULLUP);

  pinMode(SWITCH_OUT, OUTPUT);
  digitalWrite(SWITCH_OUT, LOW);

  pinMode(LED_BUILTIN, OUTPUT);

  // Attach servo
  myservo.attach(SERVO_PIN);

  // Flash LED to show that the machine is ready
  digitalWrite(LED_BUILTIN, HIGH);

  gotoPercent(50, 1, 0);
  gotoPercent(0, 1, 0);

  digitalWrite(LED_BUILTIN, LOW);

  // Read switch at startup to determine random/sequential mode
  switchState = digitalRead(SWITCH_PIN);

  if (switchState == LOW) {
    // Sequential mode
    goRandom = false;
  } 
  else {
    // Random mode
    goRandom = true;
  }

  // Seed random number generator
  randomSeed(analogRead(A5));
}


// ============================================================
// MAIN LOOP
// ============================================================

void loop() {

  switchState = digitalRead(SWITCH_PIN);

  if (switchState == LOW) {

    // If the previous switch activation was less than
    // 10 seconds ago, increase rapid switch count
    if ((millis() - lastInput) < 10000) {
      rapidCount++;
    } 
    else {
      rapidCount = 0;
    }

    lastInput = millis();

    // Fewer than 4 rapid switches:
    // perform the normal sequence
    if (rapidCount < 4) {

      seq = 0;

    } 
    else {

      // After becoming "mad", use random or sequential sequences
      if (goRandom == true) {

        seq = random(1, 10);

      } 
      else {

        seq++;

        if (seq > 9) {
          seq = 1;
        }
      }
    }

    // Run selected sequence
    if (seq == 0) Seq00();
    if (seq == 1) Seq01();
    if (seq == 2) Seq02();
    if (seq == 3) Seq03();
    if (seq == 4) Seq04();
    if (seq == 5) Seq05();
    if (seq == 6) Seq06();
    if (seq == 7) Seq07();
    if (seq == 8) Seq08();
    if (seq == 9) Seq09();

    lastInput = millis();

  } 
  else {

    delay(50);
  }

  // Turn built-in LED ON when the machine is
  // "mad" or about to become mad
  if ((millis() - lastInput < 10000) && rapidCount >= 3) {

    digitalWrite(LED_BUILTIN, HIGH);

  } 
  else {

    digitalWrite(LED_BUILTIN, LOW);
  }
}


// ============================================================
// SEQUENCE 00
// ============================================================

void Seq00() {

  gotoPercent(100, 3, 0);
  gotoPercent(0, 3, 0);
}


// ============================================================
// SEQUENCE 01
// ============================================================

void Seq01() {

  gotoPercent(100, 3, 0);
  gotoPercent(0, 1, 0);
}


// ============================================================
// SEQUENCE 02
// ============================================================

void Seq02() {

  gotoPercent(100, 1, 2000);
  gotoPercent(0, 7, 0);
}


// ============================================================
// SEQUENCE 03
// ============================================================

void Seq03() {

  gotoPercent(100, 10, 0);
  gotoPercent(75, 1, 1000);
  gotoPercent(100, 10, 0);
  gotoPercent(75, 10, 0);
  gotoPercent(100, 10, 0);
  gotoPercent(0, 5, 0);
}


// ============================================================
// SEQUENCE 04
// ============================================================

void Seq04() {

  gotoPercent(25, 1, 500);
  gotoPercent(50, 1, 500);
  gotoPercent(75, 1, 2000);
  gotoPercent(100, 10, 0);
  gotoPercent(0, 5, 0);
}


// ============================================================
// SEQUENCE 05
// ============================================================

void Seq05() {

  gotoPercent(50, 5, 0);
  gotoPercent(0, 1, 300);
  gotoPercent(75, 5, 0);
  gotoPercent(0, 1, 300);
  gotoPercent(80, 5, 1000);
  gotoPercent(70, 5, 0);
  gotoPercent(100, 10, 0);
  gotoPercent(0, 3, 0);
}


// ============================================================
// SEQUENCE 06
// ============================================================

void Seq06() {

  gotoPercent(100, 3, 0);
  gotoPercent(80, 1, 500);
  gotoPercent(100, 8, 500);
  gotoPercent(80, 1, 500);
  gotoPercent(100, 8, 500);
  gotoPercent(80, 1, 500);
  gotoPercent(50, 1, 500);
  gotoPercent(25, 1, 500);
  gotoPercent(0, 1, 0);
}


// ============================================================
// SEQUENCE 07
// ============================================================

void Seq07() {

  gotoPercent(100, 2, 0);

  for (int i = 0; i < 10; i++) {

    gotoPercent(80, 3, 0);
    gotoPercent(100, 6, 0);
  }

  gotoPercent(100, 6, 2000);
  gotoPercent(50, 1, 500);
  gotoPercent(0, 1, 0);
}


// ============================================================
// SEQUENCE 08
// ============================================================

void Seq08() {

  for (int i = 30; i <= 100; i += 10) {

    gotoPercent(i, 7, 0);
    gotoPercent(i - 30, 4, 0);
  }

  gotoPercent(0, 5, 0);
}


// ============================================================
// SEQUENCE 09
// ============================================================

void Seq09() {

  for (int i = 0; i < random(10, 20); i++) {

    gotoPercent(
      random(0, 80),
      random(1, 10),
      random(0, 500)
    );
  }

  gotoPercent(100, random(1, 10), random(0, 500));
  gotoPercent(0, random(1, 10), 0);
}


// ============================================================
// SERVO MOVEMENT FUNCTION
// ============================================================
//
// targetPC:
// 0   = starting position
// 100 = switch-hitting position
//
// steps:
// Controls movement speed.
//
// afterDelay:
// Delay after the servo reaches its target.
// ============================================================

void gotoPercent(int targetPC, int steps, int afterDelay) {

  target = POS_START +
           ((POS_END - POS_START) * targetPC * 0.01);

  while (pos != target) {

    if (target < pos) {

      if (pos - target < steps) {
        pos = target;
      } 
      else {
        pos -= steps;
      }

    } 
    else {

      if (target - pos < steps) {
        pos = target;
      } 
      else {
        pos += steps;
      }
    }

    myservo.write(pos);

    // Same 10 ms movement interval as the original code
    delay(10);
  }

  // Keep servo powered/positioned during the after-delay
  for (int delayTimer = 0;
       delayTimer <= afterDelay;
       delayTimer += 50) {

    delay(50);
  }
}