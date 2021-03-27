// by AEhere
// This code controls the IRIS-1 UAV
// 
 

#include <Servo.h>

Servo ThrottleESCServo;  // create servo object to control the ESC

int ThrottleESCPin = A2;

int intThrottlePos = 0;    // variable to store the servo position


void setup() {
  
  ThrottleESCServo.attach(ThrottleESCPin);
  

}

void loop() {
  // put your main code here, to run repeatedly:

}
