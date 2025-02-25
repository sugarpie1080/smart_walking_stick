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


namespace smart_stick 
{
    ToFSensor::ToFSensor(const char* chipname, int line): Sensor(chipname, line) {}

    void ToFSensor::initialise()
    {
        sensor.initialize();
        // Set to continous mode
        sensor.startContinuous();
        sensor.setMeasurementTimingBudget(200000);

    }
    
    void ToFSensor::getData()
    {
        
        std::cout << "Reading Distance data..." << std::endl;
        // For now, simulate getting data
        uint16_t distance = sensor.readRangeContinuousMillimeters();

        std::cout << "Distance: " << distance << "mm" << std::endl;
    }
    
    void ToFSensor::send() {
        std::cout << "Sending Distance data..." << std::endl;
    }
}