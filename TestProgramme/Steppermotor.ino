#include <Stepper.h>

int maxSteps = 2048;
Stepper Schrittmotor(maxSteps, 4, 6, 5, 7);

void setup() {
  // Set the speed of the motor
  myStepper.setSpeed(60);
}

void loop() {
  // Rotate the motor 1 full revolution clockwise
  myStepper.step(stepsPerRevolution);
  delay(1000);

  // Rotate the motor 1 full revolution counterclockwise
  myStepper.step(-stepsPerRevolution);
  delay(1000);
}
