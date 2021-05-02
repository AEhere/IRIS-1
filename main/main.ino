// by AEhere
// This code controls the IRIS-1 UAV
//

#include <Servo.h>
#include "RF24.h"

Servo ThrottleESCServo;  // create servo object to control the ESC

#define ESC_THR_PIN 3
#define SRV_ELEV_PIN 4
#define SRV_RUD_PIN 5
#define SRV_AIL_R_PIN 9
#define SRV_AIL_L_PIN 10

#define THR_CONTROL_PIN A0      //for local throttle control

#define CE_PIN  7               //radio pins
#define CSN_PIN 8

// Start the radio object
RF24 radio(CE_PIN, CSN_PIN);

int intTHRPos = 0;     // variable to store the servo position
int intRXThrottlePos = 0;   // received throttle value
int intELEVPos = 0;
int intRUDPos = 0;
int intAILPos = 0;

void setup() {

    Serial.begin(9600);


  ThrottleESCServo.attach(ESC_THR_PIN);   //Attach the ESC channel

//  pinMode(3, OUTPUT);

}

void loop() {


        intTHRPos = analogRead(THR_CONTROL_PIN);                    // reads the value of the potentiometer (value between 0 and 1023)
        ThrottleESCServo.write(map(intTHRPos, 512, 0, 10, 170));   // scale it to use it with the servo (value between 0 and 180)

        Serial.println(intTHRPos);



  delay(10);

//  intTHRPos = map(intTHRPos, 0, 180, 0, 255);
//  analogWrite(11,intTHRPos);

}
