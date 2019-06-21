#include <Wire.h>
#include <AD9833.h>

//启动第一个DDS

#define LED0_PIN       PB0      // I'm alive blinker  
#define SYN_PIN        PB3
#define FNC_PIN_DISABLE

AD9833 gen_1(1);

void setup() {

  Serial.begin(9600);
  Wire.begin();
  gpio_write_bit(GPIOB, 3, HIGH);

  Wire.beginTransmission(0x27);
  Wire.write(6); 
  Wire.write(0);//1111 1110
  Wire.write(0);
  Wire.endTransmission();

  afio_cfg_debug_ports(AFIO_DEBUG_NONE);// Stop the debug function
  SPI.begin();
  delay(1);

  Wire.beginTransmission(0x27);
  Wire.write(2); 
  Wire.write(0xFE);//1111 1110
  Wire.endTransmission();
  
  gen_1.Reset(); // Into reset mode
  gen_1.SetFrequency ( REG0, 40000 );
  gen_1.SetPhase ( REG0, 0 );
  gen_1.EnableOutput(true);  // Turn ON the output
  
  Wire.beginTransmission(0x27);
  Wire.write(2); 
  Wire.write(0xFF);//1111 1111
  Wire.endTransmission();
  
  SPI.setDataMode(SPI_MODE1);
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV256);  

  Wire.beginTransmission(0x27);
  Wire.write(2); 
  Wire.write(0xEF);//1110 1111
  Wire.endTransmission();

  SPI.transfer(0x10); // Write channel 1 value
  SPI.transfer(0);

  Wire.beginTransmission(0x27);
  Wire.write(2); 
  Wire.write(0xFF);//1111 1111
  Wire.endTransmission();
}


void loop() {

  delay(5000);           // wait 5 seconds for next scan
}
