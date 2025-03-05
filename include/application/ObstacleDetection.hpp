
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

class ObstacleDetectionPub : public BasePublisher<MotorCommands, MotorCommandsPubSubType> {
    public:
        ObstacleDetectionPub();
    };
    

class ObstacleDetectionSub : public BaseSubscriber<ToFData, ToFDataPubSubType> {
protected:
    class OSSubListener : public SubListener<ToFData> {
    public:
        OSSubListener(ObstacleDetectionPub &pub) : publisher_(pub) {}  
        void on_data_available(DataReader* reader) override;
        int convert_distance_to_duty_cycle(float distance);
    private:
        ObstacleDetectionPub &publisher_;  
    };
    OSSubListener listener_;
    ObstacleDetectionPub publisher_;

public:
    ObstacleDetectionSub();
    void set_listener(DataReader* reader);
};


}

#endif // TOF_DATA_SUBSCRIBER_HPP
