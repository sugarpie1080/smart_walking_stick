#include <iostream>
#include <chrono>
#include <thread>
#include "INA219.hpp"

int main() {
    std::cout << "Starting INA219 test on Raspberry Pi 5..." << std::endl;

    // Create INA219 instance with 0.1 Ohm shunt resistor, max 3.2A, I2C address 0x42
    INA219 sensor(0.1f, 3.2f, 0x42);

    try {
        // Initialize and calibrate the sensor
        sensor.init();
        sensor.calibrate(0.1f, 3.2f);

        while (true) {
            float bus_voltage = sensor.read_voltage();
            float shunt_voltage = sensor.read_shunt_voltage();
            float current = sensor.read_current();
            float power = sensor.read_power();

            std::cout << "----------------------------------------" << std::endl;
            std::cout << "Bus Voltage    : " << bus_voltage << " V" << std::endl;
            std::cout << "Shunt Voltage  : " << shunt_voltage << " mV" << std::endl;
            std::cout << "Current        : " << current << " A" << std::endl;
            std::cout << "Power          : " << power << " W" << std::endl;

            std::this_thread::sleep_for(std::chrono::seconds(2));
        }

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
