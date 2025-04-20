#include "INA219.hpp"

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <cstring>
#include <stdexcept>
#include <iostream>

// Original constructor
INA219::INA219(const std::string& i2c_device_path, uint8_t address)
    : _address(address) {
    _file_descriptor = open(i2c_device_path.c_str(), O_RDWR);
    if (_file_descriptor < 0) {
        throw std::runtime_error("Failed to open I2C device.");
    }
    if (ioctl(_file_descriptor, I2C_SLAVE, _address) < 0) {
        throw std::runtime_error("Failed to acquire bus access to INA219.");
    }
}

// New constructor that BatteryMonitor expects
INA219::INA219(float shunt_ohms, float max_expected_amps, int i2c_address)
    : _address(i2c_address), _max_expected_amps(max_expected_amps) {
    // You can hardcode or pass the I2C path as needed
    std::string i2c_device = "/dev/i2c-1";

    _file_descriptor = open(i2c_device.c_str(), O_RDWR);
    if (_file_descriptor < 0) {
        throw std::runtime_error("Failed to open I2C device.");
    }

    if (ioctl(_file_descriptor, I2C_SLAVE, _address) < 0) {
        throw std::runtime_error("Failed to acquire bus access to INA219.");
    }

    // Initialize other calibration values here if needed
    _current_lsb = 0.0f;
    _power_lsb = 0.0f;
}

INA219::~INA219() {
    if (_file_descriptor >= 0) {
        close(_file_descriptor);
    }
}

// Stub methods to prevent linker errors (implement as needed)
void INA219::configure(VoltageRange, Gain, AdcResolution, AdcResolution) {}
void INA219::calibrate(int, float, float) {}
void INA219::wake() {}
float INA219::voltage() { return 0.0f; }
float INA219::shunt_voltage() { return 0.0f; }
float INA219::supply_voltage() { return 0.0f; }
float INA219::current() { return 0.0f; }
float INA219::power() { return 0.0f; }

uint16_t INA219::read_register(uint8_t) { return 0; }
void INA219::write_register(uint8_t, uint16_t) {}
