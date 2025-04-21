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
#include <BatteryMonitor.hpp>

// DDS includes
#include <BasePublisher.hpp>
#include <ToFDataPubSubTypes.hpp>
#include <MotorCommandsPubSubTypes.hpp>
#include <BatteryPubSubTypes.hpp>

namespace smart_stick{
    /**
     * @class DDSCommunicator
     * @brief DDSCommunicator class for publishing data to DDS
     * Derived from the CallbackInterface for both ToFSensor and MotorMove classes
     */
    class DDSCommunicator: 
    public ToFSensor::CallbackInterface, 
    public MotorMove::CallbackInterface, 
    public BatteryMonitor::CallbackInterface  
    {
        public:
            /**
             * @brief Constructor for DDSCommunicator
             * @param tof Pointer to the ToFSensor object
             * @param mm Pointer to the MotorMove object
             * @param bat Pointer to the Battery object
             */
            DDSCommunicator(ToFSensor* tof, MotorMove* mm, BatteryMonitor* bat);

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
             * @brief Callback function for battery percentage from Battery
             * @param battery_percentage Battery level percentage
             */
            void has_battery(float battery_percentage) override;  
            /**
             * @brief Worker for publishing data to DDS
             */
            void worker();

        private:
            void publish_distance();
            void publish_duty_cycle();
            void publish_battery();
            std::pair<int32_t, int32_t> getCurrentTime();

            std::condition_variable cv;
            std::mutex mutex;
            bool distance_ready, duty_cycle_ready, battery_ready;
            float last_distance,last_battery;
            int last_duty_cycle;
            std::thread worker_thread;
            std::atomic_bool running;
            BasePublisher<ToFData, ToFDataPubSubType> tof_pub;
            BasePublisher<MotorCommands, MotorCommandsPubSubType> motor_pub;
            BasePublisher<Battery, BatteryPubSubType> battery_pub;
    };
}

#endif // DDS_COMMUNICATOR_HPP

