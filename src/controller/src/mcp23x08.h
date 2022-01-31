//----------------------------------------------------------------------------
// Name        : mcp23x08.h
// Purpose     : MCP23X08 IO-Expander Chip Controller Class
// Description : 
//               This class intended for control of MCP23X08 IO-expander
//               integrated circuits.
//
//               Interrupts may be setup by applying values to the appropriate
//               registers to desired specification as described in the
//               datasheet. Improvements to this class might add interrupt
//               functionality better mirroring that of the Arduino framework.
//
// Platform    : Multiple
// Framework   : Arduino
// Language    : C++
// Copyright   : MIT License 2021, John Greenwell
// Requires    : External Libraries : N/A
//               Custom Libraries   : N/A
//----------------------------------------------------------------------------
#ifndef MCP23X08_H
#define MCP23X08_H

namespace PeripheralIO {

class MCP23X08 {
public:
    MCP23X08();

    void begin(uint8_t address=0, TwoWire& wire=Wire);
    // Initialize IO to the MCP23X08 with mode I2C (Wire)
    // Input address is only the 3 LSB matching device external biasing
    // Wire must be initialized beforehand

    void begin(uint8_t address, uint8_t cs_pin, SPIClass& spi=SPI);
    // Initialize IO to the MCP23X08 with mode SPI (hardware)
    // Input address is only the 2 LSB matching device external biasing
    // Wire must be initialized beforehand

    bool pinMode(uint8_t pin, uint8_t mode) const;
    // Set input/output mode on individual pin 0-7
    // Modes: OUTPUT, INPUT, INPUT_PULLUP

    void portMode(uint8_t mode) const;
    // Assign same pin mode to entire GPIO port
    // e.g. portMode(OUTPUT);
    // e.g. portMode(INPUT_PULLUP);

    bool digitalWrite(uint8_t pin, uint8_t val) const;
    // Write value to individual pin 0-7
    // Pin must be already configured as output

    uint8_t digitalRead(uint8_t pin) const;
    // Read value from individual pin 0-7
    // Pin must be already configured as input

    void write(uint8_t val) const;
    // Direct write value to entire GPIO port
    // Port must be already configured as output

    void write(uint8_t reg, uint8_t val) const;
    // Direct write of value to specific register
    // e.g. write(MCP23X08_OLAT, 0xFF);

    uint8_t read() const;
    // Direct read value from entire GPIO port
    // Port must already be configured as input

    uint8_t read(uint8_t reg) const;
    // Direct read of value from specific register
    // e.g. val = read(MCP23X08_GPIO);
 
private:

    void (PeripheralIO::MCP23X08::*_mcpWrite)(uint8_t reg, uint8_t byte) const;
    uint8_t (PeripheralIO::MCP23X08::*_mcpRead)(uint8_t reg) const;

    void spiWrite(uint8_t reg, uint8_t byte) const;
    uint8_t spiRead(uint8_t reg) const;
    void i2cWrite(uint8_t reg, uint8_t byte) const;
    uint8_t i2cRead(uint8_t reg) const;

    TwoWire *_wire;
    SPIClass *_spi;
    uint8_t _address;
    uint8_t _cs;
};

// Base Address and Register Defines
extern const uint8_t MCP23X08_ADDR; // 7-bit addr
extern const uint8_t MCP23X08_IODIR;
extern const uint8_t MCP23X08_IPOL;
extern const uint8_t MCP23X08_GPINTEN;
extern const uint8_t MCP23X08_DEFVAL;
extern const uint8_t MCP23X08_INTCON;
extern const uint8_t MCP23X08_IOCON;
extern const uint8_t MCP23X08_GPPU;
extern const uint8_t MCP23X08_INTF;
extern const uint8_t MCP23X08_INTCAP;
extern const uint8_t MCP23X08_GPIO;
extern const uint8_t MCP23X08_OLAT;

}

#endif