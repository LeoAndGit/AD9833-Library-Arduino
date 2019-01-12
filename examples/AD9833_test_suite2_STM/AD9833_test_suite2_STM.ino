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
FNC_PIN_1 PA1 (IC1)
FNC_PIN_2 PA2 (IC2)
*/


#include <AD9833.h>        

#define RUNNING       F("\tRUNNING")
#define NOT_RUNNING   F("")
#define ON            F("ON")
#define OFF           F("OFF")
#define LED_PIN       PB0      // I'm alive blinker  
#define FNC_PIN_1     PA1
#define FNC_PIN_2     PA2                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            // Any digital pin. Used to enable SPI transfers (active LO  


//--------------- Create an AD9833 object ---------------- 
// Note, SCK and MOSI must be connected to CLK and DAT pins on the AD9833 for SPI
// -----      AD9833 ( FNCpin, referenceFrequency = 25000000UL )
AD9833 gen_1(FNC_PIN_1);       // Defaults to 25MHz internal reference frequency
AD9833 gen_2(FNC_PIN_2);

void setup() { 
    pinMode(LED_PIN,OUTPUT);
    digitalWrite(LED_PIN, HIGH);

    while (!Serial);          // Delay until terminal opens
    Serial.begin(9600);

    // This MUST be the first command after declaring the AD9833 object
    SPI.begin();
    delay(100);
    digitalWrite(FNC_PIN_1, LOW);
    digitalWrite(FNC_PIN_2, LOW);
    gen_1.Reset();
    gpio_write_bit(GPIOA, 1, HIGH);
    gpio_write_bit(GPIOA, 2, HIGH);

    //gen_1.ApplySignal(SINE_WAVE,REG0,1000);
    gen_1.SetFrequency ( REG0, 22000 );
    gen_1.SetPhase ( REG0, 0 );
    //gen_1.SetOutputSource ( REG0, REG0 );
    gen_2.SetFrequency ( REG0, 22000 );
    gen_2.SetPhase ( REG0, 0 );
    //gen_2.SetOutputSource ( REG0, REG0 );

    //gen_2.ApplySignal(SINE_WAVE,REG0,1000);
    digitalWrite(FNC_PIN_1, LOW);
    digitalWrite(FNC_PIN_2, LOW);
    gen_1.EnableOutput(true);  // Turn ON the output
    //gen_2.EnableOutput(true);  // Turn ON the output
    gpio_write_bit(GPIOA, 1, HIGH);
    gpio_write_bit(GPIOA, 2, HIGH);

    gen_1.SetPhase ( REG0, 90 );
}

void loop() { 
delay(1);
}
