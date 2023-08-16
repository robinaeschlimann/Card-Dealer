#include <Stepper.h> // Hinzufügen der Programmbibliothek.
int SPU = 2048; // Schritte pro Umdrehung.
Stepper Motor(SPU, 4,5,6,7); // Der Schrittmotor erhält die Bezeichnung "Motor" und es wird angegeben an welchen Pins der Motor angeschlossen ist.

void setup() //Hier beginnt das Setup.
{
Motor.setSpeed(10); // Angabe der Geschwindigkeit in Umdrehungen pro Minute.
}

void loop() {
Motor.step(200); // Der Motor macht 2048 Schritte, das entspricht einer Umdrehung.
delay(1000); // Durch diese Pause bleibt der Motor nach der Drehung für eine Sekunde stehen.
Motor.step(-200); // Der Motor macht durch das Minuszeichen 2048 Schritte in die andere Richtung.
delay(1000); // Durch diese Pause bleibt der Motor nach der Drehung für eine Sekunde stehen.
}

/* #include <Stepper.h>

int maxSteps = 2048;
Stepper StepperMotor(maxSteps, 4, 5, 6, 7);
//Stepper StepperMotor(maxSteps, 6, 4, 7, 5);
//Stepper StepperMotor(maxSteps, 4, 5, 6, 7);
//Stepper StepperMotor(maxSteps, 6, 5, 4, 7);
//Stepper StepperMotor(maxSteps, 5, 6, 7, 4);

void setup() {
  // Set the speed of the motor
  StepperMotor.setSpeed(60);
}

void loop() {
  // Rotate the motor 1 full revolution clockwise
  StepperMotor.step(200);
  delay(1000);

  // Rotate the motor 1 full revolution counterclockwise
  StepperMotor.step(-200);
  delay(1000);
}
 */