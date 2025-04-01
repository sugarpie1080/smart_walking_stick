/**
 * @file ObstacleDetection.hpp
 * @author Felicity Lipscomb
 * @brief Obstacle Detection header file
 * @version 0.1
 * @date 2025-03-05
 * 
 * @copyright Copyright (c) 2025
 * Contains a subscriber for the ToFDataTopic and a publisher for the MotorCommandsTopic.
 * The subscriber listens for messages and converts the distance to a duty cycle for the motor.
 * The publisher sends the duty cycle to the listener.
 */
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

#include <thread> 
#include <atomic>
using namespace eprosima::fastdds::dds;

namespace smart_stick {

/**
 * @brief Obstacle Detection Publisher Class. Derived from the BasePublisher Class.
 * 
 */
class ObstacleDetectionPub : public BasePublisher<MotorCommands, MotorCommandsPubSubType> {
    public:
        /**
         * @brief Construct a new ObstacleDetectionPub object
         * 
         */
        ObstacleDetectionPub();
    };
    

/**
 * @brief Obstacle Detection Subscriber Class. Derived from the BaseSubscriber Class.
 * 
 */
class ObstacleDetectionSub : public BaseSubscriber<ToFData, ToFDataPubSubType> {
protected:
    /**
     * @brief Obstacle Detection Subscriber Listener Class. Derived from the SubListener Class.
     * 
     */
    class OSSubListener : public SubListener<ToFData> {
    public:
        /**
         * @brief Construct a new OSSubListener object
         * 
         * @param pub Publisher for the MotorCommands message.
         */
        OSSubListener(ObstacleDetectionPub &pub) : publisher_(pub) {}  
        /**
         * @brief Callback function for when data is available.
         * 
         * @param reader FastDDS DataReader object.
         */
        void on_data_available(DataReader* reader) override;
        /**
         * @brief Converts the distance value from the ToF sensor to a motor duty cycle.
         * 
         * @param distance distance value from the ToF sensor in mm.
         * @return int duty cycle value for the motor.
         */
        int convert_distance_to_duty_cycle(float distance);

        
    private:
        ObstacleDetectionPub &publisher_;  
    };
    OSSubListener listener_;
    ObstacleDetectionPub publisher_;

    std::atomic<bool> stop_flag_;
    std::thread subscriber_thread_;

public:
    /**
     * @brief Construct a new ObstacleDetectionSub object
     * 
     */
    ObstacleDetectionSub();
    /**
     * @brief Set the listener for the subscriber.
     * 
     * @param reader FastDDS DataReader object.
     */
    void set_listener(DataReader* reader);
    void start();
    void stop();

};


}

#endif // OBSTACLE_DETECTION_HPP
