/**
 * @file sensors.cpp
 * @author Felicity Lipscomb
 * @brief Functions fr the Sensor class
 * @version 0.1
 * @date 2025-02-25
 * 
 * @copyright Copyright (c) 2025
 * 
 */
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
        else 
        {
            std::cout << "Chip opened" << std::endl;
        }
        // Get the GPIO line
        line = gpiod_chip_get_line(chip, pin);
        if (!line) {
            std::cerr << "Failed to get GPIO line!" << std::endl;
            gpiod_chip_close(chip);
            exit(1);
        }
        // Request the line as falling edge events
        if (gpiod_line_request_falling_edge_events(line, "temp") < 0) {
            std::cerr << "Failed to request GPIO line as input!" << std::endl;
            gpiod_chip_close(chip);
            exit(1);
        }
    }
    
    void Sensor::initialise()
    {   
        std::cout << "Initalise Sensor..." << std::endl;
    }

    Sensor::~Sensor() {
        if (chip) {
            gpiod_chip_close(chip);
        }
    }    
}
