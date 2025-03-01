/**
 * @file sensors.hpp
 * @author Felicity Lipscomb
 * @brief A sensor class to initalise and retrieve sensor data
 * @version 0.1
 * @date 2025-02-24
 * 
 */

#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <iostream>
#include <gpiod.h>
#include <unistd.h>

namespace smart_stick
{
/**
 * @class Sensor 
 * @brief A parent class to initalise and retrieve data from a given sensor
 * 
 */
class Sensor {
   
    public:
        /**
         * @brief Construct a new Sensor object
         * 
         * @param chipname name of the GPIO chip used for the interrupt
         * @param pin pin number of interrupt pin
         */
        Sensor(const char* chipname, int pin);
        virtual ~Sensor();
        
        /**
         * @brief Initialises the sensor
         * 
         */
        virtual void initialise();
        /**
         * @brief Retrieves data from the sensor
         * 
         */
        virtual void getData();
        /**
         * @brief Sending data using a publisher
         * 
         */
        virtual void send();
        /**
         * @brief Starts the interrupt listening process
         * 
         */
        void startListening();
    protected:
        const char* chipname;
        int pin;
        struct gpiod_line* line;
        struct gpiod_chip* chip;
};
}
#endif // SENSOR_HPP
