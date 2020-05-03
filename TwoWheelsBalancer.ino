////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////

#include <Arduino_FreeRTOS.h>
#include "AFMotor.h"

////////////////////////////////////////////////////////////////////////
// Global Variables
////////////////////////////////////////////////////////////////////////

// Number of steps per output rotation
// Change this as per your motor's specification
const uint16_t stepsPerRevolutionMotor1 = 96;
const uint16_t stepsPerRevolutionMotor2 = 96;

uint8_t stepsPerIteration = 1;
uint8_t speedMotor1 = 80;
uint8_t speedMotor2 = 80;
uint8_t senseMotor1 = FORWARD;
uint8_t senseMotor2 = FORWARD;

////////////////////////////////////////////////////////////////////////
// Tasks Prototypes
////////////////////////////////////////////////////////////////////////

void TaskBlink( void *pvParameters );

void TaskStepper1(void *pvParameters);
void TaskControlSpeedMotor1(void *pvParameters);

void TaskStepper2(void *pvParameters);
void TaskControlSpeedMotor2(void *pvParameters);

////////////////////////////////////////////////////////////////////////
// Setup
////////////////////////////////////////////////////////////////////////

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  
  xTaskCreate(
    TaskBlink
    ,  (char *) "Blink"   // A name just for humans
    ,  128  // Stack size
    ,  NULL
    ,  5  // priority
    ,  NULL);

  xTaskCreate(
    TaskStepper1
    ,  (char *) "Stepper1"   // A name just for humans
    ,  128  // Stack size
    ,  NULL
    ,  1  // priority
    ,  NULL);
    
  xTaskCreate(
    TaskControlSpeedMotor1
    ,  (char *) "ControlSpeedMotor0"   // A name just for humans
    ,  128  // Stack size
    ,  NULL
    ,  3  // priority
    ,  NULL);

  xTaskCreate(
    TaskStepper2
    ,  (char *) "Stepper2"   // A name just for humans
    ,  128  // Stack size
    ,  NULL
    ,  2  // priority
    ,  NULL);
    
  xTaskCreate(
    TaskControlSpeedMotor2
    ,  (char *) "ControlSpeedMotor2"   // A name just for humans
    ,  128  // Stack size
    ,  NULL
    ,  4  // priority
    ,  NULL);
  
//  BaseType_t xReturned;
//  TaskHandle_t xHandle = NULL;
//  
//  // Now set up two tasks to run independently.
//  xReturned = xTaskCreate(
//    TaskBlink
//    ,  (char *) "Blink"   // A name just for humans
//    ,  128  // Stack size
//    ,  NULL
//    ,  2  // priority
//    ,  &xHandle );

}

void loop()
{
  // Empty. Things are done in Tasks.
}

////////////////////////////////////////////////////////////////////////
// Tasks Definition
////////////////////////////////////////////////////////////////////////

void TaskBlink(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);

  for (;;) // A Task shall never return or exit.
  {
    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
    digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
  }
}

void TaskStepper1(void *pvParameters)
{
  (void) pvParameters;
  
  // connect motor to port #1 (M1 and M2)
  AF_Stepper motor1(stepsPerRevolutionMotor1, 1);

  // Stepper motor initialisation
  motor1.setSpeed(speedMotor1);  // rpm
  motor1.release(); // release all coils so that it can moove freely

  for (;;) // A Task shall never return or exit.
  {
    motor1.setSpeed(speedMotor1);  // rpm
    motor1.step(stepsPerIteration, senseMotor1, DOUBLE);
  }
}

void TaskControlSpeedMotor1(void *pvParameters)
{
  (void) pvParameters;

  int maxVal = 80;
  int minVal = 1;

  int iterator = 0;

  for (;;) // A Task shall never return or exit.
  {
    for(iterator = minVal; iterator <= maxVal; iterator++){
      speedMotor2 = iterator;
      vTaskDelay( 100 / portTICK_PERIOD_MS );
    }
    for(iterator = maxVal; iterator >= minVal; iterator--){
      speedMotor2 = iterator;
      vTaskDelay( 100 / portTICK_PERIOD_MS );
    }
  }
}

void TaskStepper2(void *pvParameters)
{
  (void) pvParameters;
  
  // connect motor to port #2 (M3 and M4)
  AF_Stepper motor2(stepsPerRevolutionMotor2, 2);

  // Stepper motor initialisation
  motor2.setSpeed(speedMotor2);  // rpm
  motor2.release(); // release all coils so that it can moove freely

  for (;;) // A Task shall never return or exit.
  {
    motor2.setSpeed(speedMotor2);  // rpm
    motor2.step(stepsPerIteration, senseMotor2, DOUBLE);
  }
}

void TaskControlSpeedMotor2(void *pvParameters)
{
  (void) pvParameters;

  int maxVal = 80;
  int minVal = 1;

  int iterator = 0;

  for (;;) // A Task shall never return or exit.
  {
    for(iterator = minVal; iterator <= maxVal; iterator++){
      speedMotor2 = iterator;
      vTaskDelay( 100 / portTICK_PERIOD_MS );
    }
    for(iterator = maxVal; iterator >= minVal; iterator--){
      speedMotor2 = iterator;
      vTaskDelay( 100 / portTICK_PERIOD_MS );
    }
  }
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
///*
// * Stepper Motor Related Functions
//  Serial.println("Single coil steps");
//  //motor.step(96, FORWARD, SINGLE);
//  //motor.step(96, BACKWARD, SINGLE);
//
//  Serial.println("Double coil steps"); // Double coils, greater torque
//  //motor.step(96, FORWARD, DOUBLE);
//  //motor.step(96, BACKWARD, DOUBLE);
//
//  Serial.println("Interleave coil steps"); // Needs double amount of steps
//  //motor.step(96, FORWARD, INTERLEAVE);
//  //motor.step(96, BACKWARD, INTERLEAVE);
//
//  Serial.println("Micrsostep steps"); // No aparent result
//  //motor.step(96, FORWARD, MICROSTEP);
//  //motor.step(96, BACKWARD, MICROSTEP);
// * */
////////////////////////////////////////////////////////////////////////
