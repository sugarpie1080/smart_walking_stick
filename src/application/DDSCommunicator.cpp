
#include <DDSCommunicator.hpp>

namespace smart_stick 
{
    DDSCommunicator::DDSCommunicator(ToFSensor* tof,MotorMove* mm):
    tof_pub("ToFDataTopic"), motor_pub("MotorCommandsTopic")
    {
        tof->register_callback(this); 
        mm->register_callback(this);   
        running = true;
        worker_thread = std::thread(&DDSCommunicator::worker, this);
    }

    DDSCommunicator::~DDSCommunicator()
    {
        running = false;
        cv.notify_all();
        worker_thread.join();
        
    }

    void DDSCommunicator::has_distance(float distance)
    {
        {
            std::lock_guard<std::mutex> lock(mutex);
            distance_ready = true;
            last_distance = distance;
        }
        cv.notify_all();
    }

    void DDSCommunicator::publish_distance()
    {
        
        ToFData message;
        auto [sec, nanosec] = getCurrentTime();
        message.sec(sec);
        message.nanosec(nanosec);
        message.distance(last_distance);
        tof_pub.publish(message);
        distance_ready = false;
        
    }

    void DDSCommunicator::publish_duty_cycle()
    {
        MotorCommands message;
        auto [sec, nanosec] = getCurrentTime();
        message.sec(sec);
        message.nanosec(nanosec);
        message.duty_cycle(last_duty_cycle);
        motor_pub.publish(message);
        duty_cycle_ready = false;
        
    }

    void DDSCommunicator::worker()
    {
        while (running)
        {
            std::unique_lock<std::mutex> lock(mutex);
            cv.wait(lock);
            if(running)
            {
                if (distance_ready)
                {
                    publish_distance();
                }
                if (duty_cycle_ready)
                {
                    publish_duty_cycle();
                }
            }
            
        }
    }

    void DDSCommunicator::has_duty(int duty_cycle)
    {
        {
            std::lock_guard<std::mutex> lock(mutex);
            duty_cycle_ready = true; 
            last_duty_cycle = duty_cycle;
        }
        cv.notify_all();

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