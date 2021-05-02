// by AEhere
// This code controls the IRIS-1 UAV
//

#include "SPI.h"
#include <Servo.h>
#include "RF24.h"
#include "printf.h"

Servo ThrottleESCServo;  // create servo object to control the ESC

#define ESC_THR_PIN 3
#define SRV_ELEV_PIN 4
#define SRV_RUD_PIN 5
#define SRV_AIL_R_PIN 9
#define SRV_AIL_L_PIN 10

#define THR_CONTROL_PIN A0      //for local throttle control

#define CE_PIN  7               //radio pins
#define CSN_PIN 8

// Create the radio object
RF24 radio(CE_PIN, CSN_PIN);

byte addresses[][6] = {"1Node","2Node"};

unsigned long intTHRPos = 0;     // variable to store the servo position
int intRXThrottlePos = 0;   // received throttle value
int intELEVPos = 0;
int intRUDPos = 0;
int intAILPos = 0;



//******************************************************************************
//********************************  SETUP  *************************************
//******************************************************************************
void setup() {

    Serial.begin(115200);

    printf_begin();

    ThrottleESCServo.attach(ESC_THR_PIN);   //Attach the ESC channel

//  pinMode(3, OUTPUT);


    radio.begin();
    radio.setPALevel(RF24_PA_LOW);
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1, addresses[0]);
    radio.startListening();
    // radio.printDetails();
    delay(1000);
    Serial.println("Radio set...");
    Serial.println("Starting loop...");
}
//******************************************************************************
//********************************  LOOP  **************************************
//******************************************************************************

void loop() {


    if( radio.available() ){
        while (radio.available()) {
            radio.read( &intRXThrottlePos, sizeof(unsigned long) );

            Serial.print("RX: ");
            Serial.println(intRXThrottlePos);
            delay(100);
        }
    }

        // intTHRPos = analogRead(THR_CONTROL_PIN);                    // reads the value of the potentiometer (value between 0 and 1023)
        //ThrottleESCServo.write(map(intTHRPos, 512, 0, 10, 170));   // scale it to use it with the servo (value between 0 and 180)




  delay(1000);
}
//******************************************************************************
//******************************************************************************
//******************************************************************************
