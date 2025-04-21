
#include <DDSCommunicator.hpp>

namespace smart_stick 
{
    DDSCommunicator::DDSCommunicator(ToFSensor* tof,MotorMove* mm, BatteryMonitor* bat):
    tof_pub("ToFDataTopic"), motor_pub("MotorCommandsTopic"), battery_pub("BatteryTopic")
    {
        tof->register_callback(this); 
        mm->register_callback(this);  
        bat->register_callback(this);
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

    void DDSCommunicator::has_duty(int duty_cycle)
    {
        {
            std::lock_guard<std::mutex> lock(mutex);
            duty_cycle_ready = true; 
            last_duty_cycle = duty_cycle;
        }
        cv.notify_all();

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

    void DDSCommunicator::has_battery(float battery_percentage) {
        {
            std::lock_guard<std::mutex> lock(mutex);
            battery_ready = true;
            last_battery = battery_percentage;
            std::cout << "Hours: " << last_battery << std::endl;
        }
        cv.notify_all();
    }
    
    void DDSCommunicator::publish_battery() {
        Battery message;
        auto [sec, nanosec] = getCurrentTime();
        message.sec(sec);
        message.nanosec(nanosec);
        message.battery_percentage(last_battery);
        battery_pub.publish(message);
        battery_ready = false;
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
                    std::cout << "Publishing distance: " << last_distance << std::endl;
                    publish_distance();
                }
                if (duty_cycle_ready)
                {
                    std::cout << "Publishing duty cycle: " << last_duty_cycle << std::endl;
                    publish_duty_cycle();
                }
                if (battery_ready) {
                    std::cout << "Publishing battery: " << last_battery << std::endl;
                    publish_battery();
                }
            }
            
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