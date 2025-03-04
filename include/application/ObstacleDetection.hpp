
#ifndef OBSTACLE_DETECTION_HPP
#define OBSTACLE_DETECTION_HPP

// Publisher Include
#include <BasePublisher.hpp>
// Subscriber includes
#include <BaseSubscriber.hpp>
#include <SubListener.hpp>
#include <fastdds/dds/subscriber/SampleInfo.hpp>

// Topic includes
#include <ToFDataPubSubTypes.h>
#include <MotorCommandsPubSubTypes.h>

using namespace eprosima::fastdds::dds;

namespace smart_stick {

class ObstacleDetectionSub : public BaseSubscriber<ToFData, ToFDataPubSubType> {
protected:
    class OSSubListener : public SubListener<ToFData> {
    public:
        void on_data_available(DataReader* reader) override;
    };
    OSSubListener listener_;

public:
    ObstacleDetectionSub();
    void set_listener(DataReader* reader);
};

class ObstacleDetectionPub : public BasePublisher<MotorCommands, MotorCommandsPubSubType> {
    public:
        ObstacleDetectionPub();
    };


}

#endif // TOF_DATA_SUBSCRIBER_HPP
