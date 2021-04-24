// by AEhere
// This code controls the IRIS-1 UAV
//

#include <Servo.h>

Servo ThrottleESCServo;  // create servo object to control the ESC

#define THR_ESC_PIN 3
#define THR_CONTROL_PIN A0

#include "RF24.h"

#define CE_PIN  7
#define CSN_PIN 8

// Start the radio object
RF24 radio(CE_PIN, CSN_PIN);

int intThrottlePos = 0;    // variable to store the servo position
int intRXThrottlePos = 0;   
int value;

void setup() {

    Serial.begin(9600);


  ThrottleESCServo.attach(THR_ESC_PIN);   //Attach the ESC channel
//  pinMode(3, OUTPUT);

}

void loop() {

  
        intThrottlePos = analogRead(THR_CONTROL_PIN);                    // reads the value of the potentiometer (value between 0 and 1023)
        ThrottleESCServo.write(map(intThrottlePos, 512, 0, 10, 170));   // scale it to use it with the servo (value between 0 and 180)

        Serial.println(intThrottlePos);



  delay(10);

//  intThrottlePos = map(intThrottlePos, 0, 180, 0, 255);
//  analogWrite(11,intThrottlePos);

}
