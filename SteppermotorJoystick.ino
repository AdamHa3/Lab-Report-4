#include <Stepper.h>

const int stepsPerRevolution = 2048;  // for 28BYJ-48
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

// Joystick pins
int joyX = A0;  // direction
int joyY = A1;  // speed

void setup() {
  Serial.begin(9600);
}

void loop() {
  int xVal = analogRead(joyX); // direction
  int yVal = analogRead(joyY); // speed

  // Map joystick Y-axis to speed (RPM)
  int motorSpeed = map(yVal, 0, 1023, 0, 15); // max 15 RPM
  myStepper.setSpeed(motorSpeed);

  // Map joystick X-axis to direction
  int steps = 0;
  if (xVal < 400) {
    steps = -5;  // move counter-clockwise
  } else if (xVal > 600) {
    steps = 5;   // move clockwise
  } // else joystick in middle → no movement

  myStepper.step(steps);

  // Debug info
  Serial.print("Joystick X: "); Serial.print(xVal);
  Serial.print(" | Y: "); Serial.print(yVal);
  Serial.print(" | Speed: "); Serial.print(motorSpeed);
  Serial.print(" RPM | Steps: "); Serial.println(steps);

  delay(20); // small delay for smooth control
}