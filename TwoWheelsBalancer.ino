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
const uint16_t stepsPerRevolutionMotor1 = 48; // 4SPM-24D6ZA 18DEC91MA
const uint16_t stepsPerRevolutionMotor2 = 96; // 6Z281B

uint8_t stepsPerIteration = 1;
uint16_t speedMotor1 = 30;
uint16_t speedMotor2 = 30;
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
// Motor Information
////////////////////////////////////////////////////////////////////////
//- 4SPM-24D6ZA 18DEC91MA (Unipolar - 6 wires)
//  - 7.5 DEG 12.5 Ohm
//  - 48 steps per revolution
//  - coil 1:
//    - yellow: 12.6 ohms to red
//    - red: middle coil
//    - orange: 12.8 ohms to red
//  - coil 2:
//    - brown: 12.6 ohms to white
//    - white: middle coil
//    - black: 12.8 ohms to white
//  - black: common (GND)
//  - Arduino Motor Shield L293D connection
//
//  Spinning sense: left hand rule in shaft direction
//  | X2 shield | wire  |
//  | A1  | yellow      |
//  | A2  | orange      |
//  | GND | red + white |
//  | B1  | brown       |
//  | B2  | black       |

//- 6Z281B (Unipolar - 5 wires)
//  - 96 steps per revolution
//  - coil 1:
//    - brown: 4 (50.5 ohms to black)
//    - orange: 2 (48.8 ohms to black)
//  - coil 2:
//    - red: 1 (50.5 ohms to black)
//    - grey: 3 (50.5 ohms to black)
//  - black: common (GND)
//  - Arduino Motor Shield L293D connection
//
//  Spinning sense: left hand rule in shaft direction
//  | X2 shield | wire |
//  | A1  | red     |
//  | A2  | grey    |
//  | GND | black   |
//  | B1  | orange  |
//  | B2  | brown   |
////////////////////////////////////////////////////////////////////////
