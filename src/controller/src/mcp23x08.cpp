//----------------------------------------------------------------------------
// Name        : mcp23x08.cpp
// Purpose     : MCP23X08 IO-Expander Chip Controller Class
// Description : This source file accompanies header file mcp23x08.h
// Platform    : Multiple
// Framework   : Arduino
// Language    : C++
// Copyright   : MIT License 2021, John Greenwell
//----------------------------------------------------------------------------

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "mcp23x08.h"

namespace PeripheralIO {

MCP23X08::MCP23X08()
: _wire(nullptr),
  _spi(nullptr),
  _address(0),
  _cs(0)
{ }

/*!
    @brief Initialize MCP23X08 using I2C
    @param address 3 LSB matching device external biasing
    @param wire I2C object connected to the device
*/
void MCP23X08::begin(uint8_t address, TwoWire& wire) {
    _address = MCP23X08_ADDR | (address & 0x07);
    _wire = &wire;
    _mcpWrite = &PeripheralIO::MCP23X08::i2cWrite;
    _mcpRead = &PeripheralIO::MCP23X08::i2cRead;
}

/*!
    @brief Initialize MCP23X08 using hardware SPI
    @param address 2 LSB matching device external biasing
    @param cs_pin CS pin number
    @param spi SPI object connected to the device
*/
void MCP23X08::begin(uint8_t address, uint8_t cs_pin, SPIClass& spi) {
    _address = (MCP23X08_ADDR << 1) | ((address & 0x03) << 1);
    _cs = cs_pin;
    _spi = &spi;
    _mcpWrite = &PeripheralIO::MCP23X08::spiWrite;
    _mcpRead = &PeripheralIO::MCP23X08::spiRead;
    ::pinMode(_cs, OUTPUT);
    ::digitalWrite(_cs, HIGH);
}

/*!
    @brief Set mode for specific pin
    @param pin Pin to change IO mode
    @param mode IO Mode (i.e. OUTPUT, INPUT, INPUT_PULLUP)
    @return Boolean true for completion, false for bad input
*/
bool MCP23X08::pinMode(uint8_t pin, uint8_t mode) const {
    uint8_t data = 0;
    if (pin > 7) return false;
    data = read(MCP23X08_IODIR);
    if (mode == INPUT) { 
        data |= (1 << pin);
    } else if (mode == OUTPUT) {
        data &= ~(1 << pin);
    } else if (mode == INPUT_PULLUP){
        data |= (1 << pin);
        write(MCP23X08_GPPU, read(MCP23X08_GPPU) | (1 << pin));
    } else {
        return false;
    }
    write(MCP23X08_IODIR, data);
    return true;
}

/*!
    @brief Assign same pin mode to entire GPIO port
    @param mode IO Mode (i.e. OUTPUT, INPUT, INPUT_PULLUP)
*/
void MCP23X08::portMode(uint8_t mode) const {
    if (mode == INPUT) { 
        write(MCP23X08_IODIR, 0xFF);
    } else if (mode == OUTPUT) {
        write(MCP23X08_IODIR, 0x00);
    } else if (mode == INPUT_PULLUP){
        write(MCP23X08_GPPU, 0xFF);
        write(MCP23X08_IODIR, 0xFF);
    }
}

/*!
    @brief Set value for specific pin
    @param pin Pin to set
    @param val Logic level (i.e. HIGH, LOW)
    @result Boolean true for completion, false for bad input
*/
bool MCP23X08::digitalWrite(uint8_t pin, uint8_t val) const {
    uint8_t data = 0;
    if (pin > 7) return false;
    data = read(MCP23X08_GPIO);
    data = (val == HIGH) ? (data | 1 << pin) : (data & ~(1 << pin));
    write(MCP23X08_GPIO, data);
    return true;
}

/*!
    @brief Read value on specific pin
    @param pin Pin to read
    @result Value read
*/
uint8_t MCP23X08::digitalRead(uint8_t pin) const {
    if (pin > 7) return 0x00;
    return ((read(MCP23X08_GPIO) >> pin) & 0x01);
}

/*!
    @brief Write to entire GPIO port
    @param val Value to write to GPIO port
*/
void MCP23X08::write(uint8_t val) const {
    write(MCP23X08_OLAT, val);
}

/*!
    @brief Write value to specific register
    @param reg Register to access
    @param val Value to write to register
*/
void MCP23X08::write(uint8_t reg, uint8_t val) const {
    (this->*_mcpWrite)(reg, val);
}

/*!
    @brief Read from entire GPIO port
    @return Value read from GPIO port
*/
uint8_t MCP23X08::read() const {
    return read(MCP23X08_GPIO);
}

/*!
    @brief Read value from specific register
    @param reg Register to access
    @return Value read from register
*/
uint8_t MCP23X08::read(uint8_t reg) const {
    return (this->*_mcpRead)(reg);
}

// Private: Hardware SPI Write Function
void MCP23X08::spiWrite(uint8_t reg, uint8_t byte) const {
    ::digitalWrite(_cs, LOW);
    _spi->transfer(_address);
    _spi->transfer(reg);
    _spi->transfer(byte);
    ::digitalWrite(_cs, HIGH);
}

// Private: Hardware SPI Read Function
uint8_t MCP23X08::spiRead(uint8_t reg) const {
    uint8_t data = 0;
    ::digitalWrite(_cs, LOW);
    _spi->transfer(_address | 0x01);
    _spi->transfer(reg);
    data = _spi->transfer(0);
    ::digitalWrite(_cs, HIGH);
    return data;
}

// Private: Hardware I2C Write Function
void MCP23X08::i2cWrite(uint8_t reg, uint8_t byte) const {
    _wire->beginTransmission(_address);
    _wire->write(reg);
    _wire->write(byte);
    _wire->endTransmission();
}

// Private: Hardware I2C Read Function
uint8_t MCP23X08::i2cRead(uint8_t reg) const {
    uint8_t data = 0;
    _wire->beginTransmission(_address);
    _wire->write(reg);
    _wire->endTransmission(0);
    _wire->requestFrom(_address, (uint8_t)1);
    if (_wire->available()) data = Wire.read();
    _wire->endTransmission();
    return data;
}

// Base Address and Register Defines
const uint8_t MCP23X08_ADDR    = 0x20; // 7-bit addr
const uint8_t MCP23X08_IODIR   = 0x00;
const uint8_t MCP23X08_IPOL    = 0x01;
const uint8_t MCP23X08_GPINTEN = 0x02;
const uint8_t MCP23X08_DEFVAL  = 0x03;
const uint8_t MCP23X08_INTCON  = 0x04;
const uint8_t MCP23X08_IOCON   = 0x05;
const uint8_t MCP23X08_GPPU    = 0x06;
const uint8_t MCP23X08_INTF    = 0x07;
const uint8_t MCP23X08_INTCAP  = 0x08;
const uint8_t MCP23X08_GPIO    = 0x09;
const uint8_t MCP23X08_OLAT    = 0x0A;

}