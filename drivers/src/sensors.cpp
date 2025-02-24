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
        // Request the line as input with pull-up
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

    // Based on the button interrupt code
    void Sensor::startListening()
    {
        // bool pressed = false;
        while (true) 
        {
            int value = gpiod_line_get_value(line);
            std::cout << value << std::endl;
            if (value < 0) {
                std::cerr << "Error reading GPIO value!" << std::endl;
                break;
            }
            if (value == 1) { // Button pressed (active low)
                // if (!pressed) {
                    std::cout << "Interrupt triggered, reading data..." <<std::endl;
                    getData();
                    value = 0;
                    // pressed = true;
                // }
            } else { // Button released
                std::cout << "Error :(" << std::endl;
                // pressed = false;
            }
        }
    }
    
}
