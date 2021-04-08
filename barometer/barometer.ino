// by AEhere
// This code serves to test a MBP280 barometer with an LCD screen
// while controlling an ESC to spin an AC motor

#include <Servo.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <LiquidCrystal.h>

#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)

Adafruit_BMP280 bmp; // I2C
//Adafruit_BMP280 bmp(BMP_CS); // hardware SPI
//Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void(* resetFunc) (void) = 0;   // A function to reset the device

Servo ThrottleESCServo;  // create servo object to control the ESC

#define THR_ESC_PIN 3
#define THR_CONTROL_PIN A7

int intThrottlePos = 0;    // variable to store the servo position
int intRXThrottlePos = 0;
int value;


void setup() {
  Serial.begin(9600);
  Serial.println(F("BMP280 test"));

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("BMP280 test");
  delay(1000);

  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    lcd.setCursor(0, 1);
    lcd.print("Sensor error!");
    delay(2500);
    resetFunc();
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X1,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X4,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X4,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_125); /* Standby time. */

  pinMode(THR_CONTROL_PIN, INPUT  );
  ThrottleESCServo.attach(THR_ESC_PIN);   //Attach the ESC channel

}

void loop() {
  Serial.print(F("Temperature = "));
  Serial.print(bmp.readTemperature());
  Serial.println(" *C");

  Serial.print(F("Pressure = "));
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");

  Serial.print(F("Approx altitude = "));
  Serial.print(bmp.readAltitude(1020.2)); /* Adjusted to local forecast! */
  Serial.println(" m");

  lcd.setCursor(0, 0);
  lcd.print("Pressure [Pa]");
  lcd.setCursor(0, 1);
  lcd.print(bmp.readPressure());
  delay(10);

//  if (Serial.available()) {
//
//    char ch = Serial.read();
//    if (ch >= '0' && ch <= '9') // is this an ascii digit between 0 and 9?
//    {
//      value = (value * 10) + (ch - '0'); // yes, accumulate the value
//    }
//    else if (ch == 10)  // is the character the newline character
//    {
//      intRXThrottlePos = value;
//      value = 0; // reset val to 0 ready for the next sequence of digits
//    }
//
//    Serial.println(intRXThrottlePos);
//
//    ThrottleESCServo.write(map(intRXThrottlePos, 0, 100, 0, 180));
//
//  }
//  else if (!Serial.available()) {

    intThrottlePos = analogRead(THR_CONTROL_PIN);                    // reads the value of the potentiometer (value between 0 and 1023)
    ThrottleESCServo.write(map(intThrottlePos, 0, 1023, 30, 120));   // scale it to use it with the servo (value between 0 and 180)

//  }

  Serial.println(intThrottlePos);
}
