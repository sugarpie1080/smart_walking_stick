/**
 * @file MotorMove.hpp
 * @author Felicity Lipscomb
 * @brief Class for moving the motor based on the commands.
 * @version 0.2
 * @date 2025-04-05
 */
#ifndef MOTOR_MOVE_HPP
#define MOTOR_MOVE_HPP


#include <iostream>
#include <mutex>
#include <atomic>
#include <thread>
#include <condition_variable>
// GPIO includes
#include <gpiod.h>
#include <unistd.h>
#include <unistd.h>
// Sensor includes
#include <rpi_pwm.h>
// Application includes
#include <ToFSensor.hpp>

namespace smart_stick {
/**
 * @class MotorMove
 * @brief Class for moving the motor based on the commands.
 * Derived from CallbackInterface for the ToFSensor class.
 * 
 * This class is responsible for moving the motor based on
 * the distance from the ToFSensor.
 * It uses a separate thread to handle the motor movement
 * and a callback interface to communicate with the ToFSensor.
 */
class MotorMove : public ToFSensor::CallbackInterface {

    public:
        /**
         * @brief Constructor for the MotorMove class
         * 
         * @param tof Pointer to the ToFSensor object
         */
        MotorMove(ToFSensor* tof);
        /**
         * @brief Destructor for the MotorMove class
         */
        ~MotorMove();

        /**
         * @brief Callback function for distance from ToFSensor
         */
        void has_distance(float distance) override;

        struct CallbackInterface
        {
            /**
             * @brief Callback function for duty cycle
             */
            virtual void has_duty(int duty_cycle) = 0;
        };
        /**
         * @brief Register a callback interface for the motor
         */
        void register_callback(CallbackInterface* ci);


    private:
        /**
         * @brief Function to convert distance to duty cycle
         * 
         * @param distance Distance from the ToFSensor
         * @return int Duty cycle for the motor
         */
        int convert_distance_to_duty_cycle(float distance);
        /**
         * @brief Worker function for moving the motor.
         * This function runs in a separate thread and waits for distance data to be ready.
         * It uses a condition variable to wait for data to be ready and then moves the motor.
         */
        void worker();

        RPI_PWM pwm;
        std::atomic_bool running;
        std::thread motor_thread;
        std::vector<CallbackInterface*> callbackInterfaces;
        std::mutex mutex;
        std::condition_variable cv;
        float distance = 0;
        // Constants for Motor Control
        const int PWM_MAX = 100;
        const int DISTANCE_MIN = 5;
        const int DISTANCE_MAX = 2000;
        const float DECAY_FACTOR = 400.0f;
    };
}

#endif // TOF_DATA_SUBSCRIBER_HPP
