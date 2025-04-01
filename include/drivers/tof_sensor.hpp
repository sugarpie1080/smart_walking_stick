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

// Driver Includes
#include <VL53L0X.hpp>
#include <gpiod.h>
#include <unistd.h>
#include <atomic>
#include <mutex>
#include <vector>
#include <thread>

namespace smart_stick
{
    /**
     * @class TofSensor
     * @brief Time of Flight Sensor Class
     * 
     */

     #define ISR_TIMEOUT 1 // sec

    class ToFSensor
    {
        public:
            /**
             * @brief Construct a new ToFSensor object
             * 
             * @param chipname name of the GPIO chip used for the interrupt
             * @param line pin number of interrupt pin
             */
            ToFSensor(const char* chipname, int pin);
            /**
             * @brief Initalises ToF sensor
             * 
             */

            ~ToFSensor();
            struct CallbackInterface {
            /**
             * Called when a new distance is available
             **/
                virtual void has_distance(float distance) = 0;
            };
            
            void initialise(); 
          
            void register_callback(CallbackInterface* ci);
            
            void start();
    
    

        private:
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

#endif


