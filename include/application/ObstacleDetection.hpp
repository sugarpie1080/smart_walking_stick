
#ifndef OBSTACLE_DETECTION_HPP
#define OBSTACLE_DETECTION_HPP

// Publisher Include
#include <BasePublisher.hpp>
// Subscriber Include
#include <BaseSubscriber.hpp>
#include <SubListener.hpp>
#include <fastdds/dds/subscriber/SampleInfo.hpp>
// Message Types Include
#include <ToFDataPubSubTypes.h>
#include <MotorCommandPubSubTypes.h>

#endif // OBSTACLE_DETECTION_HPP

namespace smart_stick {

    class ObstacleDetection
    {
    public:
        // Subscriber class for ToFData messages.
        class ObstacleDetectionSub: BaseSubscriber<ToFData, ToFDataPubSubType>;
        // Publisher class for MotorCommand messages.
        class ObstacleDetectionPub: BasePublisher<MotorCommand, MotorCommandPubSubType>;
        ObstacleDetection();
        ~ObstacleDetection();
        void run();
    };

    class ObstacleDetection::ObstacleDetectionSub
    {
        protected:
            class ObstacleDetectionListener: SubListener<ToFData>
            {
                public:
                    void on_data_available(DataReader* reader) override;
            };
            ObstacleDetectionListener listener_;
        public:
            ObstacleDetectionSub();
            void set_listener(DataReader* reader);
};

    }
}