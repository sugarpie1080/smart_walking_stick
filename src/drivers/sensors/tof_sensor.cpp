/**
 * @file tof_sensor.cpp
 * @author Felicity Lipscomb
 * @brief Functions for ToF Sensor Class
 * @version 0.1
 * @date 2025-02-25
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <tof_sensor.hpp>
// Driver Includes
#include <VL53L0X.hpp>
#include <iostream>
#include <ctime>
#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"


namespace smart_stick 
{
    ToFSensor::ToFSensor(const char* chipname, int line): Sensor(chipname, line) {}

    void ToFSensor::initialise()
    {
        sensor.initialize();
        // Set to continous mode
        sensor.startContinuous();
        sensor.setMeasurementTimingBudget(200000);

    }
    
    void ToFSensor::getData()
    {
        
        std::cout << "Reading Distance data..." << std::endl;
        // For now, simulate getting data
        uint16_t distance = sensor.readRangeContinuousMillimeters();

        std::cout << "Distance: " << distance << "mm" << std::endl;
    }
    
    void ToFSensor::send() {
        std::cout << "Sending Distance data..." << std::endl;
    }

    class tofPub : public rclcpp::None
    {
        public:
        tofPub()
        : Node("tof_publisher"), count_(0)
        {
            publisher = this->create_publisher<std_msgs::msg::String>("topic", 10);
            timer_ = this->create_wall_timer(
                500ms, std::bind(&tofPub::timer_callback, this));
        }

        private:
        void timer_callback()
        {
            auto message = std_msgs::msg::String();

            std::time_t result = std::time(nullptr);
            std::cout << std::asctime(std::localtime(&result)) << result << " seconds since the Epoch\n";

            message.data = std::to_string(count_++) + result + getData();
            RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
            publisher_->publish(message);
        }
        rclcpp::TimerBase::SharedPtr timer_;
        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
        size_t count_;
    };
}