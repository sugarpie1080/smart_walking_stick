#include "INA219.hpp"
#include <unistd.h>  // for usleep
#include <cmath>

INA219::INA219(float shunt_resistor_value, float max_expected_amps, uint8_t i2c_addr)
    : _i2c_addr(i2c_addr), _shunt_resistor_value(shunt_resistor_value), _current_LSB(0.0f), _i2c() {
    calibrate(shunt_resistor_value, max_expected_amps);
}

void INA219::init() {
    // 0x399F is a common default config for 32V range, 320mV gain, 12-bit ADC
    uint16_t config = 0x399F;
    write_register(INA219_REG_CONFIG, config);
    usleep(10000); // Sleep for 10ms
}

void INA219::calibrate(float shunt_resistor_value, float max_expected_amps) {
    _current_LSB = max_expected_amps / 32768.0f;
    uint16_t cal = static_cast<uint16_t>(0.04096f / (_current_LSB * shunt_resistor_value));
    write_register(INA219_REG_CALIBRATION, cal);
}

float INA219::read_voltage() {
    uint16_t raw = read_register(INA219_REG_BUSVOLTAGE);
    raw >>= 3;  // 13-bit result
    return raw * 0.004f;  // Each bit = 4mV
}

float INA219::read_shunt_voltage() {
    int16_t raw = static_cast<int16_t>(read_register(INA219_REG_SHUNTVOLTAGE));
    return raw * 0.01f;  // Each bit = 10uV
}

float INA219::read_current() {
    int16_t raw = static_cast<int16_t>(read_register(INA219_REG_CURRENT));
    return raw * _current_LSB;
}

float INA219::read_power() {
    uint16_t raw = read_register(INA219_REG_POWER);
    return raw * (_current_LSB * 20.0f);  // Power LSB = 20 * current_LSB
}

uint16_t INA219::read_register(uint8_t reg) {
    uint8_t buffer[2] = {0};
    _i2c.readBytes(_i2c_addr, reg, 2, buffer);
    return (buffer[0] << 8) | buffer[1];
}

void INA219::write_register(uint8_t reg, uint16_t value) {
    uint8_t buffer[2];  // Only 2 bytes are needed for uint16_t
    buffer[0] = (value >> 8) & 0xFF;  // High byte
    buffer[1] = value & 0xFF;         // Low byte

    I2Cdev::writeBytes(_i2c_addr, reg, 2, buffer);  // 2 is the length of data
}

