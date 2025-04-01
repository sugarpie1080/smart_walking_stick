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
#include <vector>
#include <thread>
namespace smart_stick
{
/**
 * @class Sensor 
 * @brief A parent class to initalise and retrieve data from a given sensor
 * 
 */

 #define ISR_TIMEOUT 1 // sec

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
         * @brief Get the Line object
         * 
         * @return struct gpiod_line* 
         */
        struct gpiod_line *getLine() { return line; } 

        struct SensorCallbackInterface {
        /**
         * Called when a new sample is available.
         * This needs to be implemented in a derived
         * class by the client. Defined as abstract.
         * \param e If falling or rising.
         **/
            virtual void hasEvent(gpiod_line_event& e) = 0;
        };

        void registerCallback(SensorCallbackInterface* ci) {
            adsCallbackInterfaces.push_back(ci);
            }
        
        void start();
        void stop();

        void gpioEvent(gpiod_line_event& event);

    private:

        virtual void worker();
        bool running = false;
        std::vector<SensorCallbackInterface*> adsCallbackInterfaces;
        std::thread thr;

    protected:
        const char* chipname;
        int pin;
        struct gpiod_line* line;
        struct gpiod_chip* chip;
};
}
#endif // SENSOR_HPP
