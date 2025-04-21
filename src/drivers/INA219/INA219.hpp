#ifndef INA219_HPP
#define INA219_HPP

#include <cstdint>
#include <I2Cdev.hpp>

class INA219 {
public:
    // Constructor
    INA219(float shunt_resistance_ohms, float max_expected_amps, uint8_t i2c_addr = 0x40);

    // Configuration
    void init();
    void calibrate(float shunt_resistor_value, float max_expected_amps);

    // Measurements
    float read_voltage();        // Bus voltage (V)
    float read_shunt_voltage();  // Shunt voltage (mV)
    float read_current();        // Current (A)
    float read_power();          // Power (W)

private:
    uint16_t read_register(uint8_t reg);
    void write_register(uint8_t reg, uint16_t value);

    // Constants for INA219 register addresses
    static constexpr uint8_t INA219_REG_CONFIG        = 0x00;
    static constexpr uint8_t INA219_REG_SHUNTVOLTAGE  = 0x01;
    static constexpr uint8_t INA219_REG_BUSVOLTAGE    = 0x02;
    static constexpr uint8_t INA219_REG_POWER         = 0x03;
    static constexpr uint8_t INA219_REG_CURRENT       = 0x04;
    static constexpr uint8_t INA219_REG_CALIBRATION   = 0x05;

    uint8_t _i2c_addr;
    float _shunt_resistor_value;
    float _current_LSB;
    I2Cdev _i2c;
};

#endif // INA219_HPP
