/**
 * @file ToFSensor.hpp
 * @author Felicity Lipscomb
 * @brief Time of Flight sensor class
 * @version 0.3
 * @date 2025-04-05
 * 
 *  Driver copyright: Copyright (c) 2016 Pololu Corporation
 */
#ifndef TOF_SENSOR_HPP
#define TOF_SENSOR_HPP

#include <atomic>
#include <mutex>
#include <vector>
#include <thread>

// Driver Includes
#include <VL53L0X.hpp>
// GPIO includes
#include <gpiod.h>
#include <unistd.h>

namespace smart_stick
{
     #define ISR_TIMEOUT 1 // sec
     /**
     * @class TofSensor
     * @brief Time of Flight Sensor Class.
     * 
     */
    class ToFSensor
    {
        public:
            /**
             * @brief Constructor for the ToFSensor class.
             * 
             * @param chipname name of the GPIO chip used for the interrupt
             * @param line pin number of interrupt pin
             */
            ToFSensor(const char* chipname, int pin);
            /**
             * @brief Destructor for the ToFSensor class.
             * 
             */
            ~ToFSensor();
            struct CallbackInterface {
            /**
             * Callback function for when a new distance is available.
             **/
                virtual void has_distance(float distance) = 0;
            };
            /**
             * @brief Initialises the ToF Sensor.
             * 
             */
            void initialise(); 
            /**
             * @brief Register a callback interface for the ToF Sensor.
             */
            void register_callback(CallbackInterface* ci);
            /**
             * @brief Initialises the GPIO chip and line.
             */
            void start();
    
    

        private:
            /**
             * @brief Worker function for the ToF Sensor.
             * This function runs in a separate thread and handles the interrupt from the GPIO line.
             * It reads the distance from the ToF sensor and calls the callback interface.
             */
            void worker();
            std::vector<CallbackInterface*> callbackInterfaces;
            std::thread thr;
            std::atomic_bool running = false;  
            std::mutex mutex;     
            VL53L0X sensor;
            const char* chipname;
            int pin;
            struct gpiod_line* line;
            struct gpiod_chip* chip;
    };
}

#endif //TOF_SENSOR_HPP


