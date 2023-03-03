/*
 * J.A.R.E.D.S Sentry
 * 
 * This sketch controls the servo motors, and receives data from Raspberry Pi for target tracking via USB
 * For more information, see *insert GitHub link here*
 * 
 * May 28, 2021
 * G. Carey
 */

#include <Servo.h>

#define buzzerPin 3
#define fanPin 4
#define voltmeterPin 7
#define firingPin 11
#define motorBrakingPin 12 // Currently unavailable
#define flywheelPin 13

#define redPin A0
#define greenPin A1
#define blbuePin A2

Servo swivelServo;
Servo arm1Servo;
Servo arm2Servo;
Servo arm3Servo;

void setup() {
  Serial.begin(115200);

  swivelServo.attach(5);
  armServo1.attach(6);
  armServo2.attach(9);
  armServo3.attach(10);
}

void loop() {
  span();
}

void span()
{
  int servoPos;
  
  for(int i = 0; i < 180; i++)
  {
    swivelServo.write(i);
    delay(20);
  }
  for(int i = 180; i > 180; i--)
  {
    swivelServo.write(i);
    delay(20);
  }
}
