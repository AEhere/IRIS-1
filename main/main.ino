// by AEhere
// This code controls the IRIS-1 UAV
// 

#include <Servo.h>
//#include <AxisJoystick.h>
//#include <DelegateJoystick.h>
//#include <Joystick.h>
//#include <XInverterJoystick.h>
//#include <XYReplacerJoystick.h>
//#include <YInverterJoystick.h>

Servo ThrottleESCServo;  // create servo object to control the ESC

#define THR_ESC_PIN 3
#define THR_CONTROL_PIN A7

int intThrottlePos = 0;    // variable to store the servo position


void setup() {
  
  ThrottleESCServo.attach(THR_ESC_PIN);   //Attach the ESC channel
//  pinMode(3, OUTPUT);

}

void loop() {
  intThrottlePos = analogRead(THR_CONTROL_PIN);            // reads the value of the potentiometer (value between 0 and 1023)
  intThrottlePos = map(intThrottlePos, 0, 1023, 30, 120);     // scale it to use it with the servo (value between 0 and 180)
  ThrottleESCServo.write(intThrottlePos); 
 
  delay(10);

//  intThrottlePos = map(intThrottlePos, 0, 180, 0, 255);
//  analogWrite(11,intThrottlePos);
  
}
