//----------------------------------------------------------------------------
// Name        : virtualport.cpp
// Purpose     : Virtual Port Class
// Description : This source file accompanies header file virtualport.h
// Platform    : Multiple
// Framework   : Arduino
// Language    : C++
// Copyright   : MIT License 2021, John Greenwell
//----------------------------------------------------------------------------

#include <Arduino.h>
#include "virtualport.h"

namespace PeripheralIO {

VirtualPort::VirtualPort()
: _pins{}
, _n_bits(0)
{ }

/*!
    @brief Assign virtual port
    @param pins Array of 8 pins arranged 0:LSB to 7:MSB
*/
void VirtualPort::begin(const uint8_t* pins) {
    _n_bits = 8;
    for (uint8_t i=0; i<_n_bits; i++) _pins[i] = pins[i];
}

/*!
    @brief Assign virtual port
    @param pins Array of N pins arranged 0:LSB to N:MSB
    @param n_bits Value N not greater than 8
*/
void VirtualPort::begin(const uint8_t* pins, uint8_t n_bits) {
    _n_bits = (n_bits > 8) ? 8 : n_bits;
    for (uint8_t i=0; i<_n_bits; i++) _pins[i] = pins[i];
}

/*!
    @brief Set mode for specific pin
    @param pin Pin to change IO mode
    @param mode IO Mode (i.e. OUTPUT, INPUT, INPUT_PULLUP)
    @return Boolean true for completion, false for bad input
*/
bool VirtualPort::pinMode(uint8_t pin, uint8_t mode) const {
    if (pin > (_n_bits-1)) return false;
    ::pinMode(_pins[pin], mode);
    return true;
}

/*!
    @brief Assign same pin mode to entire port
    @param mode IO Mode (i.e. OUTPUT, INPUT, INPUT_PULLUP)
*/
void VirtualPort::portMode(uint8_t mode) const {
    for (uint8_t i=0; i<_n_bits; i++) ::pinMode(_pins[i], mode);
}

/*!
    @brief Set value for specific pin
    @param pin Pin to set
    @param val Logic level (i.e. HIGH, LOW)
    @result Boolean true for complettion, false for bad input
*/
bool VirtualPort::digitalWrite(uint8_t pin, uint8_t val) const {
    if (pin > _n_bits) return false;
    ::digitalWrite(_pins[pin], val);
    return true;
}

/*!
    @brief Read value on specific pin
    @param pin Pin to read
    @result Value read
*/
uint8_t VirtualPort::digitalRead(uint8_t pin) const {
    if (pin > _n_bits) return -1;
    return ::digitalRead(_pins[pin]);
}

/*!
    @brief Write to entire port
    @param val Value to write to port
*/
void VirtualPort::write(uint8_t val) const {
    for (uint8_t i=0; i<_n_bits; i++)
        ::digitalWrite(_pins[i], ((val >> i) & 0x01));
}

/*!
    @brief Read from entire port
    @return Value read from port
*/
uint8_t VirtualPort::read() const {
    uint8_t data = 0;
    for (uint8_t i=0; i<_n_bits; i++) {
        data |= ::digitalRead(_pins[i]) << i;
    }
    return data;
}

}
