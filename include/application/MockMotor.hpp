/**
 * @file ToFDataSubscriber.hpp
 * @author Felicity Lipscomb
 * @brief Example Subscriber class.
 * @version 0.1
 * @date 2025-02-26
 * 
 * 
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

using namespace eprosima::fastdds::dds;

namespace smart_stick {
/**
 * @brief Example Subscriber class for ToFData messages. Derived from the BasePublisher Class.
 * 
 * To use the base example, you must declare the class 
 * with the message type and the PubSubType.
 */
class MockMotor : public BaseSubscriber<MotorCommands, MotorCommandsPubSubType> {
protected:
    /**
     * @brief Example Listener class for ToFData messages. Derived from the SubListener Class.
     * 
     * A listener class is required for every subscriber. This class contains the callback
     * function for the subscriber, which determines what actions are taken with the message.
     * 
     */
    class MockMotorListener : public SubListener<MotorCommands> {
    public:
        /**
         * @brief Callback function for the subscriber.
         * 
         * @param reader FastDDS DataReader object.
         */
        void on_data_available(DataReader* reader) override;
    };

    MockMotorListener listener_;

public:
    /**
     * @brief Construct a new ToFDataSubscriber object
     * 
     */
    MockMotor();
    /**
     * @brief Sets the listener object for the subscriber.
     * 
     * @param reader FastDDS DataReader object.
     */
    void set_listener(DataReader* reader);
};
}

#endif // TOF_DATA_SUBSCRIBER_HPP
