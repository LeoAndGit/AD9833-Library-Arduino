#include <Wire.h>

//use IIC2
//TwoWire WIRE2 (2,I2C_FAST_MODE);
//#define Wire WIRE2


void setup() {

  Serial.begin(9600);
  Wire.begin();
  Serial.println("\nI2C Scanner");
}


void loop() {
  byte error, address;

  Serial.println("Start...");
    Wire.beginTransmission(0x27);
    Wire.write(2);                              // pointer to configuration register address 0
    Wire.write(0);                            // write config register low byte

    Wire.endTransmission();


  delay(5000);           // wait 5 seconds for next scan
}
