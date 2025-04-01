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
    ToFSensor::ToFSensor(const char* chipname, int line): Sensor(chipname, line) {}

    void ToFSensor::initialise()
    {
        sensor.initialize();
        // Set to continous mode
        sensor.startContinuous();
        sensor.setMeasurementTimingBudget(20000);

    }

    void ToFSensor::hasEvent(gpiod_line_event& e) {
	    switch (e.event_type) {
	    case GPIOD_LINE_EVENT_RISING_EDGE:
		printf("Rising!\n");
		break;
	    case GPIOD_LINE_EVENT_FALLING_EDGE:
		printf("Falling\n");
		break;
	    default:
		printf("Unkown event\n");
	    }
        float help = getDistance();
	}

    
    float ToFSensor::getDistance()
    {
        
        std::cout << "Reading Distance data..." << std::endl;
        // For now, simulate getting data
        uint16_t distance = sensor.readRangeContinuousMillimeters();
        std::cout << "Distance: " << distance << "mm" << std::endl;

        return static_cast<float>(distance);

    }
    
    // void ToFSensor::send() {
    //     std::cout << "Sending Distance data..." << std::endl;
    // }

}