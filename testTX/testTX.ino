//Test transmitter code to verify data handling by the receiver



#include <SPI.h>
#include "RF24.h"
#include "printf.h"
#include <nRF24L01.h>

#define CE_PIN  7               //radio pins
#define CSN_PIN 8

RF24 radio(CE_PIN, CSN_PIN); // Create the radio object

byte addresses[][6] = {"1Node","2Node"};

// unsigned long intTestValue = 0;

void setup(){

    Serial.begin(115200);

    printf_begin();

    radio.begin();
    radio.setPALevel(RF24_PA_LOW);
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1, addresses[1]);
    // radio.stopListening();
    radio.setDataRate(RF24_250KBPS);
    radio.setAutoAck(1);            //must the RX acknowledge the tramsmission?
    radio.setRetries(5,15);
    radio.printDetails();
    delay(1000);
    Serial.println(F("Radio set..."));

} //Setup

void loop(){
    radio.stopListening();
    int intTestValue = micros();
    Serial.print(F("TX: "));
    if(!radio.write(&intTestValue,sizeof(int))){
        Serial.println(F("failure!"));
    }
    Serial.println(intTestValue);
    radio.startListening();

    delay(10);

} //Loop
