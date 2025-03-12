/**
 * @file MotorMove.hpp
 * @author Felicity Lipscomb
 * @brief Example Subscriber class.
 * @version 0.1
 * @date 2025-02-26
 * 
 */
#ifndef MOCK_MOTOR_HPP
#define MOCK_MOTOR_HPP

// Subscriber includes
#include <BaseSubscriber.hpp>
#include <SubListener.hpp>
#include <fastdds/dds/subscriber/SampleInfo.hpp>

// Topic includes
#include <MotorCommandsPubSubTypes.h>

// 
#include <iostream>
#include <gpiod.h>
#include <unistd.h>

using namespace eprosima::fastdds::dds;

namespace smart_stick {
/**
 * @brief Subscriber class for ToFData messages. Derived from the BasePublisher Class.
 * 
 * To use the base example, you must declare the class 
 * with the message type and the PubSubType.
 */
class MotorMove : public BaseSubscriber<MotorCommands, MotorCommandsPubSubType> {
protected:
    /**
     * @brief Listener class for ToFData messages. Derived from the SubListener Class.
     * 
     * A listener class is required for every subscriber. This class contains the callback
     * function for the subscriber, which determines what actions are taken with the message.
     * 
     */
    class MotorMoveListener : public SubListener<MotorCommands> {
    public:
        void setupMotor();
        
        /**
         * @brief Callback function for the subscriber.
         * 
         * @param reader FastDDS DataReader object.
         */
        void on_data_available(DataReader* reader) override;
        
        struct gpiod_line *getLine() { return line; }
    private:
        const char* chipname = "/dev/gpiochip0";
        int pin = 18;
        struct gpiod_line* line;
        struct gpiod_chip* chip;
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

     
private:
   
};
}

#endif // TOF_DATA_SUBSCRIBER_HPP
