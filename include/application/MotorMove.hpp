/**
 * @file MotorMove.hpp
 * @author Felicity Lipscomb
 * @brief Subscriber class for moving the motor based on the commands.
 * @version 0.1
 * @date 2025-03-12
 */
#ifndef MOTOR_MOVE_HPP
#define MOTOR_MOVE_HPP

// Subscriber includes
// #include <BaseSubscriber.hpp>
// #include <SubListener.hpp>
// #include <fastdds/dds/subscriber/SampleInfo.hpp>

// // Topic includes
// #include <MotorCommandsPubSubTypes.h>

// GPIO includes
#include <iostream>
#include <gpiod.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <thread>
#include "rpi_pwm.h"
#include <tof_sensor.hpp>
#include <condition_variable>
#include <mutex>
// using namespace eprosima::fastdds::dds;

namespace smart_stick {
/**
 * @brief Subscriber class for moving the motor based on the commands.
 * public BaseSubscriber<MotorCommands, MotorCommandsPubSubType> 
 * Derived from the BaseSubscriber class
 * 
 */
class MotorMove : public ToFSensor::CallbackInterface {

    public:
        MotorMove(ToFSensor* tof);
        ~MotorMove();
        void has_distance(float distance) override;

    private:
        int convert_distance_to_duty_cycle(float distance);
        void worker();
        RPI_PWM pwm;
        std::atomic_bool running;
        std::thread motor_thread;
        std::mutex mutex;
        std::condition_variable cv;
        float distance = 0;
    };
}

//     /**
//      * @brief Listener Class for the MotorMove Subscriber.
//      * 
//      */
//     class MotorMoveListener : public SubListener<MotorCommands> {
//     public:
//         explicit MotorMoveListener(MotorMove* parent) : parent_(parent) {}
        
//         /**
//          * @brief Callback function for the subscriber.
//          * 
//          * @param reader FastDDS DataReader object.
//          */
//         void on_data_available(DataReader* reader) override;
        
        
//     private:
//         MotorMove* parent_;  
//     };

//     MotorMoveListener listener_;

// public:
//     /**
//      * @brief Construct a new MotorMove object
//      * 
//      */
//     MotorMove();
//     /**
//      * @brief Sets the listener object for the subscriber.
//      * 
//      * @param reader FastDDS DataReader object.
//      */
//     void set_listener(DataReader* reader);
//     /**
//      * @brief Get the Line object
//      * 
//      * @return struct gpiod_line* 
//      */
//     // struct gpiod_line *getLine() { return line; }
//     void start(DataReader* reader);
//     void stop();
     


#endif // TOF_DATA_SUBSCRIBER_HPP
