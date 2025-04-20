#ifndef INA219_H
#define INA219_H

#include <cstdint>
#include <string>

class INA219 {
public:
    enum VoltageRange {
        RANGE_16V = 0,
        RANGE_32V
    };

    enum Gain {
        GAIN_1_40MV = 0,
        GAIN_2_80MV,
        GAIN_4_160MV,
        GAIN_8_320MV
    };

    enum AdcResolution {
        ADC_9BIT = 0,
        ADC_10BIT,
        ADC_11BIT,
        ADC_12BIT,
        ADC_2SAMP,
        ADC_4SAMP,
        ADC_8SAMP,
        ADC_16SAMP,
        ADC_32SAMP,
        ADC_64SAMP,
        ADC_128SAMP
    };

    INA219(const std::string& i2c_device_path, uint8_t address);
    INA219(float shunt_ohms, float max_expected_amps, int i2c_address);  // New constructor

    ~INA219();

    void configure(VoltageRange voltage_range, Gain gain, AdcResolution bus_adc, AdcResolution shunt_adc);
    void calibrate(int bus_volts_max, float shunt_volts_max, float max_expected_amps);
    void wake();

    float voltage();
    float shunt_voltage();
    float supply_voltage();
    float current();
    float power();

private:
    int _file_descriptor;
    uint8_t _address;
    float _current_lsb;
    float _power_lsb;
    float _max_expected_amps;

    uint16_t read_register(uint8_t reg);
    void write_register(uint8_t reg, uint16_t value);

    static constexpr int REG_CONFIG        = 0x00;
    static constexpr int REG_SHUNT_VOLTAGE = 0x01;
    static constexpr int REG_BUS_VOLTAGE   = 0x02;
    static constexpr int REG_POWER         = 0x03;
    static constexpr int REG_CURRENT       = 0x04;
    static constexpr int REG_CALIBRATION   = 0x05;

    static constexpr float SHUNT_MV_LSB = 0.01f;
    static constexpr float BUS_MV_LSB   = 4.0f;
};

#endif // INA219_H
