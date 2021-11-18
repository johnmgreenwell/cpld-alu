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

    void begin();
    // Initilize IO to the MCP23X08 with default mode I2C (hardware)
    // Assumes address bits A2-A0 are all externally biased low 

    void begin(uint8_t address);
    // Initialize IO to the MCP23X08 with mode I2C (hardware)
    // Input address is only the 3 LSB matching device external biasing

    void begin(uint8_t address, uint8_t cs_pin);
    // Initialize IO to the MCP23X08 with mode SPI (hardware)
    // Input address is only the 3 LSB matching device external biasing
    // Value of cs_pin is pin number connected to CS pin on the device

    void begin(uint8_t address,
               void (*mcpIOBegin_ptr)(void), 
               void (*mcpWrite_ptr)(uint8_t, uint8_t),
               uint8_t (*mcpRead_ptr)(uint8_t));
    // Advanced: Initilize custom IO to the MCP23X08
    // Custom IO allows arbitrary software SPI or I2C via pointers
    // Format must strictly match the following and accomplish description
    //
    // address: 8-bit, MSB of addr at MSB of byte (LSB for internal R/W bit)
    //
    // void mcpIOBegin_ptr();
    // All necessary IO setup required for subsequent functions
    //
    // void mcpWrite_ptr(uint8_t reg, uint8_t val);
    // Write value val to register reg (ref datasheet for details)
    //
    // uint8_t mcpRead_ptr(uint8_t reg);
    // Return value from register reg (ref datasheet for details)

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

    void (PeripheralIO::MCP23X08::*_IOBegin)(void) const;
    void (PeripheralIO::MCP23X08::*_mcpWrite)(uint8_t reg, uint8_t byte) const;
    uint8_t (PeripheralIO::MCP23X08::*_mcpRead)(uint8_t reg) const;
    void (*_userMcpWrite)(uint8_t reg, uint8_t byte);
    uint8_t (*_userMcpRead)(uint8_t reg);

    void spiWrite(uint8_t reg, uint8_t byte) const;
    uint8_t spiRead(uint8_t reg) const;
    void i2cWrite(uint8_t reg, uint8_t byte) const;
    uint8_t i2cRead(uint8_t reg) const;
    void userWrite(uint8_t reg, uint8_t byte) const;
    uint8_t userRead(uint8_t reg) const;

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