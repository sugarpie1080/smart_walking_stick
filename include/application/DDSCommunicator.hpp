/**
 * @file DDSCommunicator.hpp
 * @author Felicity Lipscomb
 * @brief DDSCommunicator class for publishing data to DDS
 * @version 0.1
 * @date 2025-02-25
 * 
 * This class is responsible for publishing data from the ToFSensor and MotorMove classes to DDS. 
 * It implements the CallbackInterface for both classes and uses a separate thread to handle the publishing.
 * This is then used by the Webapp to display the data.
 */
#ifndef DDS_COMMUNICATOR_HPP
#define DDS_COMMUNICATOR_HPP

#include <utility>
#include <chrono>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <iostream>

// Application includes
#include <ToFSensor.hpp>
#include <MotorMove.hpp>

// DDS includes
#include <BasePublisher.hpp>
#include <ToFDataPubSubTypes.hpp>
#include <MotorCommandsPubSubTypes.hpp>

namespace smart_stick{
    /**
     * @class DDSCommunicator
     * @brief DDSCommunicator class for publishing data to DDS
     * Derived from the CallbackInterface for both ToFSensor and MotorMove classes
     */
    class DDSCommunicator: 
    public ToFSensor::CallbackInterface, MotorMove::CallbackInterface 
    {
        public:
            /**
             * @brief Constructor for DDSCommunicator
             * @param tof Pointer to the ToFSensor object
             * @param mm Pointer to the MotorMove object
             */
            DDSCommunicator(ToFSensor* tof,MotorMove* mm);

            /**
             * @brief Destructor for DDSCommunicator
             */
            ~DDSCommunicator();
            /**
             * @brief Callback function for distance from ToFSensor
             * @param distance Distance from the ToFSensor
             */
            void has_distance(float distance) override;
            /**
             * @brief Callback function for duty cycle from MotorMove
             * @param duty_cycle Duty cycle for the motor
             */
            void has_duty(int duty_cycle) override;
            /**
             * @brief Worker for publishing data to DDS
             * This function runs in a separate thread and waits for data to be ready to publish.
             * It uses a condition variable to wait for data to be ready and then publishes the data.
             */
            void worker();
            

        
        private:
            /**
             * @brief Publish the distance data to DDS
             * This function is called when the distance data is ready to be published.
             */
            void publish_distance();
            /**
             * @brief Publish the duty cycle data to DDS
             * This function is called when the duty cycle data is ready to be published.
             */
            void publish_duty_cycle();
            /**
             * @brief Get the current time in seconds and nanoseconds
             * @return std::pair<int32_t, int32_t> Current time in seconds and nanoseconds
             */
            std::pair<int32_t, int32_t> getCurrentTime();
            
            std::condition_variable cv;
            std::mutex mutex;
            bool distance_ready, duty_cycle_ready;
            float last_distance;
            int last_duty_cycle;
            std::thread worker_thread;
            std::atomic_bool running;
            BasePublisher<ToFData, ToFDataPubSubType> tof_pub;
            BasePublisher<MotorCommands, MotorCommandsPubSubType> motor_pub;
    };
}

#endif //DDS_COMMUNICATOR_HPP
