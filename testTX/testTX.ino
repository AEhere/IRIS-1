//Test transmitter code to verify data handling by the receiver



#include "SPI.h"
#include "RF24.h"
#include "printf.h"

#define CE_PIN  7               //radio pins
#define CSN_PIN 8

// Create the radio object
RF24 radio(CE_PIN, CSN_PIN);

byte addresses[][6] = {"1Node","2Node"};

unsigned long intTestValue = 0;

void setup(){

    Serial.begin(115200);

    printf_begin();

    radio.begin();
    radio.setPALevel(RF24_PA_LOW);
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1, addresses[1]);
    radio.stopListening();
    radio.printDetails();
    delay(1000);
    Serial.println("Radio set...");
}

void loop(){
    intTestValue = 1000.0*(1.0 + sin(millis()));
    Serial.print("TX: ");
    if(!radio.write(&intTestValue,sizeof(unsigned long))){
        Serial.println("failure!");
    }
    Serial.println(intTestValue);
    delay(1000);

}
