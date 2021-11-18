//----------------------------------------------------------------------------
// Name        : main.cpp
// Purpose     : CPLD-ALU Project Controller Main
// Description : 
//               This project is an exercise in microcontroller interface with
//               an 8-bit ALU instantiated on a CPLD. The ILI9340 TFT LCD is
//               used to display the exchange with the ALU.
//
//               The instruction set for the ALU is as follows:
//
//               M,S1,S0  |  Output F
//               ---------|----------------
//                0 0 0   |  complement(A)
//                0 0 1   |  A AND B
//                0 1 0   |  identity(A)
//                0 1 1   |  A OR B
//                1 0 0   |  decrement(A)
//                1 0 1   |  A + B
//                1 1 0   |  A - B
//                1 1 1   |  increment(A)
//
// Platform    : Teensy 4.0
// Framework   : Arduino
// Language    : C++
// Copyright   : MIT License 2021, John Greenwell
// Requires    : External Libraries : Adafruit_ILI9340.h (and dependencies)
//               Custom Libraries   : mcp23x08.h
//                                    virtualport.h
//----------------------------------------------------------------------------

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include "Adafruit_ILI9340.h"
#include "mcp23x08.h"
#include "virtualport.h"

// CONFIG: Pin Assignment
const uint8_t PORT_F_PINS[8] = {2, 3, 4, 5, 6, 7, 8, 9};
const uint8_t CONTROL_PINS[3] = {17, 16, 15};
const uint8_t OV_PIN      = 23;
const uint8_t CO_PIN      = 22;
const uint8_t LCD_RST_PIN = 14;
const uint8_t LCD_DC_PIN  = 20;
const uint8_t LCD_CS_PIN  = 10;

// CONFIG: Initial Values
const int8_t A_START = 0;
const int8_t B_START = 50;

// Peripheral Objects
Adafruit_ILI9340 lcd = Adafruit_ILI9340(LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN);
PeripheralIO::MCP23X08 port_A;
PeripheralIO::MCP23X08 port_B;
PeripheralIO::VirtualPort port_F;
PeripheralIO::VirtualPort control;

// Main program
void setup(void) {
    // Setup all IO
    port_A.begin(0x00);
    port_B.begin(0x01);
    port_F.begin(PORT_F_PINS);
    control.begin(CONTROL_PINS, 3);
    port_A.portMode(OUTPUT);
    port_B.portMode(OUTPUT);
    port_F.portMode(INPUT);
    control.portMode(OUTPUT);
    pinMode(OV_PIN, INPUT);
    pinMode(CO_PIN, INPUT);
    control.write(0x00);
    port_A.write(A_START);
    port_B.write(B_START);

    // Setup LCD
    lcd.begin();
    lcd.setRotation(2);
    lcd.fillScreen(ILI9340_BLACK);
    lcd.setTextColor(ILI9340_GREEN, ILI9340_BLACK);
    lcd.setTextSize(2);
}

// Main loop
void loop() {
    static const String op_str[8] =
        {"NOT(A) ", "A AND B", "A      ", "A OR B ",
         "A - 1  ", "A + B  ", "A - B  ", "A + 1  "};
    // Properly format display
    lcd.setCursor(0, 0);
    lcd.print("\n\nCPLD ALU Test\n\n");
    lcd.printf(" A = %-*i ", 4, (int8_t)port_A.read());
    lcd.printf("0x%0*X\n", 2, port_A.read());
    lcd.printf(" B = %-*i ", 4, (int8_t)port_B.read());
    lcd.printf("0x%0*X", 2, port_B.read());
    lcd.setCursor(192, 112);
    lcd.print("C V\n");
    // Issue each control command 0-7 and print results
    for (int8_t i=0; i<8; i++) {
        control.write(i);
        lcd.print(op_str[i]);
        if (i < 4) // Print in hex for logical
            lcd.printf(" = 0x%0*X  ", 2, port_F.read());
        else       // Print in dec for arithmetic
            lcd.printf(" = %-*i  ", 4, (int8_t)port_F.read());
        lcd.printf("%i %i\n",digitalRead(CO_PIN), digitalRead(OV_PIN));
    }
    // Increment A each loop
    port_A.write(port_A.read()+1);
    delay(2000);
}
