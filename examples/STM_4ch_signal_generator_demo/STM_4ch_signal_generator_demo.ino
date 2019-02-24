/*
STM 4-ch DDS signal generator demo
Liu 2019/2/24

This sketch demonstrates the use of the AD9833 DDS signal generator.
The library uesed in this demo is modified from the AD9833 DDS module 
library by WLWilliams.

Raw library code found at: https://github.com/Billwilliams1952/AD9833-Library-Arduino

 * This program is free software: you can redistribute it and/or modify it under 
 * the terms of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version. 
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of
 * the GNU General Public License along with this program.
 * If not, see <http://www.gnu.org/licenses/>.

This example code is in the public domain.

To make it work on a STM32 MCU
Using the first SPI port (SPI_1)
    SS    <-->  PA4 <-->  BOARD_SPI1_NSS_PIN
    SCK   <-->  PA5 <-->  BOARD_SPI1_SCK_PIN
    MISO  <-->  PA6 <-->  BOARD_SPI1_MISO_PIN
    MOSI  <-->  PA7 <-->  BOARD_SPI1_MOSI_PIN
SS pin may not be used.

LED0 Pin PB0
LED1 Pin PB1

FNC_PIN_1 PB8
FNC_PIN_2 PB9
FNC_PIN_3 PB10
FNC_PIN_4 PB11

Digi_POT_SS PB3
*/


#include <AD9833.h>

// #include "AD5144.h" // This library is not used
// The set_value() function on channel 0 is not working.
// AD5144 poti(4, PB3);

// Set initial parameter here
#define Frequency      22000  // Hz

#define Phase_1        90     // Degree
#define Phase_2        0
#define Phase_3        0
#define Phase_4        0

#define Attenuation_1  50     // Digi-pot value, 255 maximum
#define Attenuation_2  100
#define Attenuation_3  150
#define Attenuation_4  200

// Pin define
#define LED0_PIN       PB0      // I'm alive blinker  
#define FNC_PIN_1      PB8
#define FNC_PIN_2      PB9
#define FNC_PIN_3      PB10
#define FNC_PIN_4      PB11
#define Digi_POT_SS    PB3

//--------------- Create an AD9833 object ---------------- 
// Note, SCK and MOSI must be connected to CLK and DAT pins on the AD9833 for SPI
// -----      AD9833 ( FNCpin, referenceFrequency = 25000000UL )
AD9833 gen_1(FNC_PIN_1); // Defaults to 25MHz internal reference frequency
AD9833 gen_2(FNC_PIN_2);
AD9833 gen_3(FNC_PIN_3);
AD9833 gen_4(FNC_PIN_4);

void setup() { 
    afio_cfg_debug_ports(AFIO_DEBUG_NONE);// Stop the debug function

    // This MUST be the first command after declaring the AD9833 object
    SPI.begin();
    delay(1);
    // Select every DDS chips
    // Use another function for faster speed
    gpio_write_bit(GPIOB, 8, LOW);
    gpio_write_bit(GPIOB, 9, LOW);
    gpio_write_bit(GPIOB, 10, LOW);
    gpio_write_bit(GPIOB, 11, LOW);
    gen_1.Reset(); // Into reset mode
    gpio_write_bit(GPIOB, 8, HIGH);
    gpio_write_bit(GPIOB, 9, HIGH);
    gpio_write_bit(GPIOB, 10, HIGH);
    gpio_write_bit(GPIOB, 11, HIGH);

    // I don't know why these two cannot work with SetPhase( REG0, xx )
    // gen_1.ApplySignal(SINE_WAVE,REG0,22000);
    // gen_2.ApplySignal(SINE_WAVE,REG0,22000);    
    gen_1.SetFrequency ( REG0, Frequency );
    gen_1.SetPhase ( REG0, Phase_1 );
    gen_2.SetFrequency ( REG0, Frequency );
    gen_2.SetPhase ( REG0, Phase_2 );
    gen_3.SetFrequency ( REG0, Frequency );
    gen_3.SetPhase ( REG0, Phase_3 );
    gen_4.SetFrequency ( REG0, Frequency );
    gen_4.SetPhase ( REG0, Phase_4 );

    // Select every DDS chips
    gpio_write_bit(GPIOB, 8, LOW);
    gpio_write_bit(GPIOB, 9, LOW);
    gpio_write_bit(GPIOB, 10, LOW);
    gpio_write_bit(GPIOB, 11, LOW);
    gen_1.EnableOutput(true);  // Turn ON the output
    gpio_write_bit(GPIOB, 8, HIGH);
    gpio_write_bit(GPIOB, 9, HIGH);
    gpio_write_bit(GPIOB, 10, HIGH);
    gpio_write_bit(GPIOB, 11, HIGH);
    
    /*Not used
    poti.begin();
    poti.set_value(0, 0);
    poti.set_value(1, 0);
    poti.set_value(2, 100);
    poti.set_value(3, 200);
    */

    pinMode(Digi_POT_SS,OUTPUT);
    SPI.setDataMode(SPI_MODE1);
    SPI.setBitOrder(MSBFIRST);
    SPI.setClockDivider(SPI_CLOCK_DIV256);    

    digitalWrite(Digi_POT_SS, HIGH);
    digitalWrite(Digi_POT_SS, LOW); // Choose Digi-pot chip
    SPI.transfer(0x10); // Write channel 1 value
    SPI.transfer(Attenuation_1);
    digitalWrite(Digi_POT_SS, HIGH);

    digitalWrite(Digi_POT_SS, LOW);
    SPI.transfer(0x11); // Write channel 2 value
    SPI.transfer(Attenuation_2);
    digitalWrite(Digi_POT_SS, HIGH);

    digitalWrite(Digi_POT_SS, LOW);
    SPI.transfer(0x12); // Write channel 3 value
    SPI.transfer(Attenuation_3);
    digitalWrite(Digi_POT_SS, HIGH);

    digitalWrite(Digi_POT_SS, LOW);
    SPI.transfer(0x13); // Write channel 4 value
    SPI.transfer(Attenuation_4);
    digitalWrite(Digi_POT_SS, HIGH);

    pinMode(LED0_PIN,OUTPUT);
    digitalWrite(LED0_PIN, HIGH);
}

void loop() { 
delay(1000);
}
