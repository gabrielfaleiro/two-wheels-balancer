#include <Arduino_FreeRTOS.h>

// define two tasks for Blink & AnalogRead
void TaskBlink( void *pvParameters );

// the setup function runs once when you press reset or power the board
void setup() {
  BaseType_t xReturned;
  TaskHandle_t xHandle = NULL;
  
  // Now set up two tasks to run independently.
  xReturned = xTaskCreate(
    TaskBlink
    ,  (char *) "Blink"   // A name just for humans
    ,  128  // Stack size
    ,  NULL
    ,  2  // priority
    ,  &xHandle );

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

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

//#include <MotorDriver.h>
//#include <Arduino.h>
//
//#include "Arduino_FreeRTOS.h"
//#include "AFMotor.h"
//#include "Servo.h"
//
//// Number of steps per output rotation
//// Change this as per your motor's specification
//const int stepsPerRevolution = 96;
//
//// connect motor to port #2 (M3 and M4)
//AF_Stepper motor(stepsPerRevolution, 2);
//
//// create servo object to control a servo
//Servo myservo;
//
//void setup() {
//  // initialize serial communications at 9600 bps:
//  Serial.begin(9600);
//
//  // Stepper motor initialisation
//  motor.setSpeed(40);  // rpm
//  //motor.onestep(FORWARD, SINGLE);
//  motor.release(); // release all coils so that it can moove freely
//
//  // Servo initialisation
//  // PIN 9  -> SERVO_2
//  // PIN 10 -> SER1
//  // attaches the servo on pin to the servo object
//  myservo.attach(10);
//
//  // TEST: digital servo, it might be that it is not provided with enough current
//  // REF: https://www.amazon.com/LewanSoul-LD-20MG-Standard-Digital-Aluminium/dp/B073F92G2S
//  // REF: https://forum.arduino.cc/index.php?topic=500585.0
//  myservo.writeMicroseconds(1000);
//
//  delay(1000);
//}
//
//void loop() {
//
//  int pos   = 544;
//  int mPos  = 544;
//  int MPos  = 2400;
//  int incPos  = 1;
//
//  // Debugging
//  //Serial.println("debug");
//
//  // Controlling Stepper Motor
//  //////motor.step(96, FORWARD, INTERLEAVE);
//  //motor.step(96, BACKWARD, INTERLEAVE);
//
//
//  // Controlling Servo
//  // sweeps from 0 degrees to 180 degrees
//
//  /*
//  for(pos = mPos; pos <= MPos; pos += incPos)
//  {
//    myservo.writeMicroseconds(pos);
//    delay(15);
//  }
//  // sweeps from 180 degrees to 0 degrees
//  for(pos = MPos; pos >= mPos; pos -= incPos)
//  {
//    myservo.writeMicroseconds(pos);
//    delay(15);
//  }
//
//  pos = 1500;
//  myservo.writeMicroseconds(pos);
//  delay(1000);
//  */
//
//  delay(2000);
//}
//
///*
// * Stepper Motor Related Functions
//  Serial.println("Single coil steps");
//  //motor.step(96, FORWARD, SINGLE);
//  //motor.step(96, BACKWARD, SINGLE);
//
//  Serial.println("Double coil steps");
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
// 
