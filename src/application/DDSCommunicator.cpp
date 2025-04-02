
#include <DDSCommunicator.hpp>

namespace smart_stick 
{
    DDSCommunicator::DDSCommunicator(ToFSensor* tof,MotorMove* mm):
    tof_pub("ToFDataTopic"), motor_pub("MotorCommandsTopic")
    {
        tof->register_callback(this); 
        mm->register_callback(this);       
    }

    void DDSCommunicator::has_distance(float distance)
    {
        ToFData message;
        auto [sec, nanosec] = getCurrentTime();
        message.sec(sec);
        message.nanosec(nanosec);
        message.distance(distance);
        if (tof_pub.publish(message))
        {
            std::cout << "Published distance: " << distance << " mm" << std::endl;
        }
        else
        {
            std::cerr << "Failed to publish distance data." << std::endl;
        }
    }

    void DDSCommunicator::has_duty(int duty_cycle)
    {
        MotorCommands message;
        auto [sec, nanosec] = getCurrentTime();
        message.sec(sec);
        message.nanosec(nanosec);
        message.duty_cycle(duty_cycle);
        if (motor_pub.publish(message))
        {
            std::cout << "Published Duty Cycle: " << duty_cycle << " mm" << std::endl;
        }
        else
        {
            std::cerr << "Failed to publish Duty Cycle." << std::endl;
        }

    }

    std::pair<int32_t, int32_t> DDSCommunicator::getCurrentTime()
    {
        auto now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        int32_t sec = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
        int32_t nanosec = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count() % 1000000000;
        return {sec, nanosec};
    }
}