#include <sensors.hpp>

namespace smart_stick{
    Sensor::Sensor(const char* chipname, int pin) : chipname(chipname), pin(pin), chip(nullptr)
    {
        // Open the GPIO Chip
        chip = gpiod_chip_open(chipname);
        // Check if can be opened
        if (!chip) {
            std::cerr << "Failed to open GPIO chip!" << std::endl;
            exit(1);
        }
    }
    
    void Sensor::initialise()
    {
        line = gpiod_chip_get_line(chip, pin);
        if (!line) {
            std::cerr << "Failed to get GPIO line!" << std::endl;
            gpiod_chip_close(chip);
            exit(1);
        }
    }
    
}
