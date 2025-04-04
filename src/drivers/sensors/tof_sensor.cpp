/**
 * @file tof_sensor.cpp
 * @author Felicity Lipscomb
 * @brief Functions for ToF Sensor Class
 * @version 0.1
 * @date 2025-02-25
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <tof_sensor.hpp>
// Driver Includes
#include <VL53L0X.hpp>
#include <iostream>
#include <ctime>
#include <chrono>
#include <functional>
#include <memory>
#include <string>


namespace smart_stick 
{
    ToFSensor::ToFSensor(const char* chipname, int pin): chipname(chipname),
        pin(pin),chip(nullptr) {}

    void ToFSensor::start()
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
        thr = std::thread(&ToFSensor::worker,this);

    }

    void ToFSensor::register_callback(CallbackInterface* ci) {
        std::lock_guard<std::mutex> lock(mutex);
        callbackInterfaces.push_back(ci);
        }

    void ToFSensor::initialise()
    {
        sensor.initialize();
        // Set to continous mode
        sensor.startContinuous();
        sensor.setMeasurementTimingBudget(20000);

    }

    void ToFSensor::worker() {
        while (running) {
            const timespec ts = { ISR_TIMEOUT, 0 };
            // this blocks till an interrupt has happened!
            int r = gpiod_line_event_wait(line, &ts);
            // check if it really has been an event
            if (1 == r) {
                gpiod_line_event event;
                gpiod_line_event_read(line, &event);
                std::cout << "Reading Distance data..." << std::endl;
                // For now, simulate getting data
                uint16_t dist = sensor.readRangeContinuousMillimeters();
                std::cout << "Distance: " << dist << "mm" << std::endl;
        
                float distance =  static_cast<float>(dist);
                {
                    std::lock_guard<std::mutex> lock(mutex);
                    for (auto cb: callbackInterfaces)
                    {
                        cb->has_distance(distance);
                    }
                }
            } 
            else if (r < 0)
            {
                std::cout<<  "GPIO error while waiting for event.\n" <<
                " Errno: " << errno << std::endl;
            }
        }
    }





    ToFSensor::~ToFSensor() {
        std::cout << "Shutting down" << std::endl;
        if (!running) return;
        running = false;
        thr.join();
        gpiod_line_release(line);
        gpiod_chip_close(chip);
    }  
    
}