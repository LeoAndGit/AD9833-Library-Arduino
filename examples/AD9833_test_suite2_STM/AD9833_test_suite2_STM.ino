/*
 * AD9833_test_suite.ino
 * 2016 WLWilliams
 * 
 * This sketch demonstrates the use of the AD9833 DDS module library.
 * 
 * If you don't have an oscilloscope or spectrum analyzer, I don't quite know how you will
 * verify correct operation for some of the functions.
 * TODO: Add tests where the Arduino itself vereifies AD9833 basic operation.  Frequency of
 * square wave, sine/triangular wave using the A/D inputs (would need a level shifter).
 * 
 * This program is free software: you can redistribute it and/or modify it under 
 * the terms of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version. 
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of
 * the GNU General Public License along with this program.
 * If not, see <http://www.gnu.org/licenses/>.
 *
 * This example code is in the public domain.
 * 
 * Library code found at: https://github.com/Billwilliams1952/AD9833-Library-Arduino
 * 
 */

/*
To make it work on a STM32 MCU
Using the first SPI port (SPI_1)
    SS    <-->  PA4 <-->  BOARD_SPI1_NSS_PIN
    SCK   <-->  PA5 <-->  BOARD_SPI1_SCK_PIN
    MISO  <-->  PA6 <-->  BOARD_SPI1_MISO_PIN
    MOSI  <-->  PA7 <-->  BOARD_SPI1_MOSI_PIN

LED Pin PB0
FNC_PIN_1 PA1
FNC_PIN_2 PA2
*/


#include <AD9833.h>        

#define RUNNING       F("\tRUNNING")
#define NOT_RUNNING   F("")
#define ON            F("ON")
#define OFF           F("OFF")
#define LED_PIN       PB0      // I'm alive blinker  
#define FNC_PIN       PA1       // Any digital pin. Used to enable SPI transfers (active LO  


//--------------- Create an AD9833 object ---------------- 
// Note, SCK and MOSI must be connected to CLK and DAT pins on the AD9833 for SPI
// -----      AD9833 ( FNCpin, referenceFrequency = 25000000UL )
AD9833 gen(FNC_PIN);       // Defaults to 25MHz internal reference frequency

void setup() { 
    pinMode(LED_PIN,OUTPUT);

    while (!Serial);          // Delay until terminal opens
    Serial.begin(9600);

    // This MUST be the first command after declaring the AD9833 object
    gen.Begin();              // The loaded defaults are 1000 Hz SINE_WAVE using REG0
                              // The output is OFF, Sleep mode is disabled
    gen.SetFrequency(REG0,1000);
    gen.EnableOutput(false);  // Turn ON the output
}

void loop() { 

}
