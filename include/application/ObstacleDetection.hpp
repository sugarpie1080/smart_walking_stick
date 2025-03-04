
#ifndef OBSTACLE_DETECTION_HPP
#define OBSTACLE_DETECTION_HPP

// Subscriber includes
#include <BaseSubscriber.hpp>
#include <SubListener.hpp>
#include <fastdds/dds/subscriber/SampleInfo.hpp>

// Topic includes
#include <ToFDataPubSubTypes.h>

using namespace eprosima::fastdds::dds;

namespace smart_stick {
/**
 * @brief Example Subscriber class for ToFData messages. Derived from the BasePublisher Class.
 * 
 * To use the base example, you must declare the class 
 * with the message type and the PubSubType.
 */
class ObstacleDetectionSub : public BaseSubscriber<ToFData, ToFDataPubSubType> {
protected:
    /**
     * @brief Example Listener class for ToFData messages. Derived from the SubListener Class.
     * 
     * A listener class is required for every subscriber. This class contains the callback
     * function for the subscriber, which determines what actions are taken with the message.
     * 
     */
    class OSSubListener : public SubListener<ToFData> {
    public:
        /**
         * @brief Callback function for the subscriber.
         * 
         * @param reader FastDDS DataReader object.
         */
        void on_data_available(DataReader* reader) override;
    };

    OSSubListener listener_;

public:
    /**
     * @brief Construct a new ToFDataSubscriber object
     * 
     */
    ObstacleDetectionSub();
    /**
     * @brief Sets the listener object for the subscriber.
     * 
     * @param reader FastDDS DataReader object.
     */
    void set_listener(DataReader* reader);
};
}

#endif // TOF_DATA_SUBSCRIBER_HPP
