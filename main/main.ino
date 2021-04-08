// by AEhere
// This code controls the IRIS-1 UAV
//

#include <Servo.h>

Servo ThrottleESCServo;  // create servo object to control the ESC

#define THR_ESC_PIN 3
#define THR_CONTROL_PIN A7

int intThrottlePos = 0;    // variable to store the servo position
int intRXThrottlePos = 0;   
int value;

void setup() {

    Serial.begin(9600);


  ThrottleESCServo.attach(THR_ESC_PIN);   //Attach the ESC channel
//  pinMode(3, OUTPUT);

}

void loop() {

        if (Serial.available()){
        
        char ch = Serial.read();
          if(ch >= '0' && ch <= '9') // is this an ascii digit between 0 and 9?
            {
            value = (value * 10) + (ch - '0'); // yes, accumulate the value
            }
          else if (ch == 10)  // is the character the newline character
          {
            intRXThrottlePos = value;
            value = 0; // reset val to 0 ready for the next sequence of digits
          }           

        Serial.println(intRXThrottlePos);

        ThrottleESCServo.write(map(intRXThrottlePos, 0, 100, 0, 180));

        }
        else if (!Serial.available()){
          
            intThrottlePos = analogRead(THR_CONTROL_PIN);                    // reads the value of the potentiometer (value between 0 and 1023)
            ThrottleESCServo.write(map(intThrottlePos, 0, 1023, 30, 120));   // scale it to use it with the servo (value between 0 and 180)

          }
    
        Serial.println(intRXThrottlePos);



  delay(10);

//  intThrottlePos = map(intThrottlePos, 0, 180, 0, 255);
//  analogWrite(11,intThrottlePos);

}
