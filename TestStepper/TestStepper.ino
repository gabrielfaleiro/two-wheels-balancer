
#include "AFMotor.h"

const int stepsPerRevolution = 96;  // change this to fit the number of steps per revolution
// for your motor

void setup() {
  // connect motor to port #1 (M1 and M2)
  AF_Stepper motor(stepsPerRevolution, 1);

  // Stepper motor initialisation
  motor.setSpeed(10);  // rpm
  motor.release(); // release all coils so that it can moove freely
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  // step one revolution  in one direction:
  // Serial.println("clockwise");
  
  motor.step(96, FORWARD, DOUBLE);
  delay(500);
}
