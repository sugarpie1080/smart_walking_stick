/**
 * @file ObstacleDetection.cpp
 * @author Felicity Lipscomb
 * @brief Obstacle Detection implementation file. 
 * @version 0.1
 * @date 2025-03-05
 * 
 * @copyright Copyright (c) 2025
 * Contains a subscriber for the ToFDataTopic and a publisher for the MotorCommandsTopic.
 */
#include <ObstacleDetection.hpp>
#include <iostream>
namespace smart_stick {

ObstacleDetectionPub::ObstacleDetectionPub() : BasePublisher("MotorCommandsTopic") {} 

ObstacleDetectionSub::ObstacleDetectionSub() : BaseSubscriber("ToFDataTopic"),publisher_(), listener_(publisher_) {}


void ObstacleDetectionSub::set_listener(DataReader* reader) {
    reader->set_listener(&listener_);
}

void ObstacleDetectionSub::OSSubListener::on_data_available(DataReader* reader) {
    // Take the next sample
    SampleInfo info;
    ToFData message;
    if (reader->take_next_sample(&message, &info) == ReturnCode_t::RETCODE_OK) {
        if (info.valid_data) {
            // converts the distance to a duty cycle
            float distance = message.distance();
            int duty_cycle = convert_distance_to_duty_cycle(distance);
            MotorCommands motor_msg;
            // determines the current time for the timestamp
            auto now = std::chrono::system_clock::now();
            auto seconds = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
            auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();
            // prepares the message to be sent
            motor_msg.sec(static_cast<int32_t>(seconds));
            motor_msg.nanosec(static_cast<int32_t>(nanoseconds));
            motor_msg.duty_cycle(duty_cycle);
            std::cout << "Message to be sent: " << motor_msg.duty_cycle() << " at timestamp "  << motor_msg.sec() <<":"<<motor_msg.nanosec() << std::endl;           
            publisher_.publish(motor_msg);
        }
    }
}


int ObstacleDetectionSub::OSSubListener::convert_distance_to_duty_cycle(float distance)
{
    // TESTING CODE NOT ACTUAL BOUNDS
    if( distance < 100)
    {
        return 100;
    }
    else
    {
        return 0;
    }
}
}
