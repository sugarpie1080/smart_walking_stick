/**
 * @file tof_sensor.hpp
 * @author Felicity Lipscomb
 * @brief Time of Flight sensor class
 * @version 0.1
 * @date 2025-02-25
 * 
 *  Driver copyright: Copyright (c) 2016 Pololu Corporation
 */
#ifndef TEST_SENSOR_H
#define TEST_SENSOR_H

#include <sensors.hpp>
// Driver Includes
#include <VL53L0X.hpp>

namespace smart_stick
{
    /**
     * @class TofSensor
     * @brief Time of Flight Sensor Class
     * 
     */
    class ToFSensor : public Sensor
    {
        public:
            /**
             * @brief Construct a new ToFSensor object
             * 
             * @param chipname name of the GPIO chip used for the interrupt
             * @param line pin number of interrupt pin
             */
            ToFSensor(const char* chipname, int line);
            /**
             * @brief Initalises ToF sensor
             * 
             */
            void initialise() override; 
            /**
             * @brief Retrieves distance data from ToF sensor
             * 
             */
            float getDistance() override;
            /**
             * @brief Sends distance data
             * 
             */
        private:
            VL53L0X sensor;
    };
}

#endif


