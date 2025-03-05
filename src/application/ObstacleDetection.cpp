
#include <ObstacleDetection.hpp>
#include <iostream>
namespace smart_stick {


ObstacleDetectionSub::ObstacleDetectionSub() : BaseSubscriber("ToFDataTopic") {}
ObstacleDetectionPub::ObstacleDetectionPub() : BasePublisher("MotorCommandsTopic") {}

void ObstacleDetectionSub::set_listener(DataReader* reader) {
    reader->set_listener(&listener_);
}

// Callback implementation
void ObstacleDetectionSub::OSSubListener::on_data_available(DataReader* reader) {
    SampleInfo info;
    ToFData message;
    if (reader->take_next_sample(&message, &info) == ReturnCode_t::RETCODE_OK) {
        if (info.valid_data) {
            float distance = message.distance();
            int duty_cycle = convert_distance_to_duty_cycle(distance);
            MotorCommands motor_msg;
            motor_msg.index(0);
            motor_msg.duty_cycle(duty_cycle);
            std::cout << "Message to be sent: " << motor_msg.duty_cycle() << std::endl;
            ObstacleDetectionPub mypub;
            mypub.publish(motor_msg);
        }
    }
}


int ObstacleDetectionSub::OSSubListener::convert_distance_to_duty_cycle(float distance)
{
    // TESTING CODE NOT ACTUAL BOUNDS
    if( distance < 100)
    {
        return 25;
    }
    else
    {
        return 75;
    }
}
}
