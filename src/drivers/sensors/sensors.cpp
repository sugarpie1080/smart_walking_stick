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

    // To be overwritten in child classes
    void Sensor::getData()
    {
        std::cout << "Getting sensor data..." << std::endl;
        // Send the data
        send();

    } 
    // To be overwritten in child classes
    void Sensor::send()
    {
        std::cout << "Sending sensor data..." << std::endl;

    }

    void Sensor::startListening()
    {
        while (true) 
        {
            // Gets value of the interrupt
            int value = gpiod_line_get_value(line);
            if (value < 0) {
                // Triggered if value is -1, therefore an error
                std::cerr << "Error reading GPIO value!" << std::endl;
                break;
            }
            if (value == 1) { 
                    std::cout << "Interrupt triggered, reading data..." <<std::endl;
                    getData();
                    value = 0;
                    
            }
        }
    }
    
}
