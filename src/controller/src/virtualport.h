//----------------------------------------------------------------------------
// Name        : virtualport.h
// Purpose     : Virtual Port Class
// Description : 
//               This class intended for arbitrary grouping of IO pins as
//               8-bit port objects. Also supports grouping of IO pins using
//               less than 8 bits.
//
//               Expansion of this class might include operator overloads
//               to perform computation on values of virtual port, and also
//               allow for port size selection greater than 8 bits.
//
// Platform    : Multiple
// Framework   : Arduino
// Language    : C++
// Copyright   : MIT License 2021, John Greenwell
// Requires    : External Libraries : N/A
//               Custom Libraries   : N/A
//----------------------------------------------------------------------------
#ifndef VIRTUALPORT_H
#define VIRTUALPORT_H

namespace PeripheralIO {

class VirtualPort {
public:
    VirtualPort();

    void begin(const uint8_t* pins);
    // Group port as array of 8 pins arranged 0:LSB to 7:MSB

    void begin(const uint8_t* pins, uint8_t n_bits);
    // Group port as array of N pins arranged 0:LSB to N:MSB
    // where N is assigned by n_bits not greater than 8

    bool pinMode(uint8_t pin, uint8_t mode) const;
    // Set input/output mode on individual pin
    // Modes: OUTPUT, INPUT, INPUT_PULLUP

    void portMode(uint8_t mode) const;
    // Assign same pin mode to entire port
    // e.g. portMode(OUTPUT);
    // e.g. portMode(INPUT_PULLUP);

    bool digitalWrite(uint8_t pin, uint8_t val) const;
    // Write value to individual pin

    uint8_t digitalRead(uint8_t pin) const;
    // Read value from individual pin

    void write(uint8_t val) const;
    // Direct write value to entire port
    // Port must be already configured as output

    uint8_t read() const;
    // Direct read value from entire GPIO port
    // Port must already be configured as input

private:
    uint8_t _pins[8];
    uint8_t _n_bits;

};

}

#endif