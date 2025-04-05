#ifndef DDS_COMMUNICATOR_HPP
#define DDS_COMMUNICATOR_HPP

#include <tof_sensor.hpp>
#include <MotorMove.hpp>

#include <BasePublisher.hpp>
#include <ToFDataPubSubTypes.hpp>
#include <MotorCommandsPubSubTypes.hpp>
#include <utility>
#include <chrono>
#include <thread>
#include <atomic>

namespace smart_stick{
    class DDSCommunicator: 
    public ToFSensor::CallbackInterface, MotorMove::CallbackInterface 
    {
        public:
            DDSCommunicator(ToFSensor* tof,MotorMove* mm);
            ~DDSCommunicator();
            void has_distance(float distance) override;
            void has_duty(int duty_cycle) override;
            void worker();
            

        
        private:
            std::condition_variable cv;
            std::mutex mutex;
            bool distance_ready, duty_cycle_ready;
            float last_distance;
            int last_duty_cycle;
            std::thread worker_thread;
            std::atomic_bool running;
            void publish_distance();
            void publish_duty_cycle();
            std::pair<int32_t, int32_t> getCurrentTime();
            BasePublisher<ToFData, ToFDataPubSubType> tof_pub;
            BasePublisher<MotorCommands, MotorCommandsPubSubType> motor_pub;
    };
}

#endif //DDS_COMMUNICATOR_HPP
