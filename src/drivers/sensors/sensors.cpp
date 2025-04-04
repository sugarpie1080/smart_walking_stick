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
#include <thread>
namespace smart_stick{
    Sensor::Sensor(const char* chipname, int pin) : chipname(chipname), pin(pin), chip(nullptr)
    {
        
    }

    void Sensor::start()
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
        if (gpiod_line_request_both_edges_events(line, "temp") < 0) {
            std::cerr << "Failed to request GPIO line as input!" << std::endl;
            gpiod_chip_close(chip);
            exit(1);
        }
        running = true;

        std::cout << "Starting..." << std::endl;
        thr = std::thread(&Sensor::worker,this);

    }
    
    void Sensor::initialise()
    {   
        std::cout << "Initalise Sensor..." << std::endl;
    }

    void Sensor::worker() {
        while (running) {
        const timespec ts = { ISR_TIMEOUT, 0 };
        // this blocks till an interrupt has happened!
        int r = gpiod_line_event_wait(line, &ts);
        // check if it really has been an event
        if (1 == r) {
            gpiod_line_event event;
            gpiod_line_event_read(line, &event);
            gpio_event(event);
        } else if (r < 0) {
            std::cout<<  "GPIO error while waiting for event.\n" <<
            " Errno: " << errno << std::endl;

        }
        }
    }

    void Sensor::gpio_event(gpiod_line_event& event) {
        for(auto &cb: callbackInterfaces) {
            cb->has_distance(event);
        }
    }

    Sensor::~Sensor() {
        std::cout << "Shutting down" << std::endl;
        if (!running) return;
        running = false;
        gpiod_line_release(line);
        gpiod_chip_close(chip);
        thr.join();
    }    
}
