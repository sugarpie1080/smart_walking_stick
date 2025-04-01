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
#include <BaseSubscriber.hpp>
#include <SubListener.hpp>
#include <fastdds/dds/subscriber/SampleInfo.hpp>

// Topic includes
#include <MotorCommandsPubSubTypes.h>

// GPIO includes
#include <iostream>
#include <gpiod.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <thread>
#include "rpi_pwm.h"

using namespace eprosima::fastdds::dds;

namespace smart_stick {
/**
 * @brief Subscriber class for moving the motor based on the commands.
 * 
 * Derived from the BaseSubscriber class
 * 
 */
class MotorMove : public BaseSubscriber<MotorCommands, MotorCommandsPubSubType> {
protected:
    /**
     * @brief Listener Class for the MotorMove Subscriber.
     * 
     */
    class MotorMoveListener : public SubListener<MotorCommands> {
    public:
        explicit MotorMoveListener(MotorMove* parent) : parent_(parent) {}
        
        /**
         * @brief Callback function for the subscriber.
         * 
         * @param reader FastDDS DataReader object.
         */
        void on_data_available(DataReader* reader) override;
        
        
    private:
        MotorMove* parent_;  
    };

    MotorMoveListener listener_;

public:
    /**
     * @brief Construct a new MotorMove object
     * 
     */
    MotorMove();
    /**
     * @brief Sets the listener object for the subscriber.
     * 
     * @param reader FastDDS DataReader object.
     */
    void set_listener(DataReader* reader);
    /**
     * @brief Get the Line object
     * 
     * @return struct gpiod_line* 
     */
    // struct gpiod_line *getLine() { return line; }

    void writeSys(std::string filename, std::string value);

    void start(DataReader* reader);
    void stop();
     
private:
    RPI_PWM pwm;
    std::atomic<bool> stop_flag_;
    std::thread motor_thread_;
};
}

#endif // TOF_DATA_SUBSCRIBER_HPP
