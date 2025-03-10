
#include <ToFDataPublisher.hpp>
#include <ObstacleDetection.hpp>
#include <MockMotor.hpp>
#include <iostream>
#include <thread>
#include <chrono>


int main() {
    const char* chipname = "/dev/gpiochip0";  
    int line = 17; 

    smart_stick::ToFDataPublisher tof_publisher(chipname, line);
    smart_stick::ObstacleDetectionSub obstacle_sub;
    smart_stick::MockMotor motor_sub;

    // Initialise the subscribers
    obstacle_sub.init();
    obstacle_sub.set_listener(obstacle_sub.reader_);

    motor_sub.init();
    motor_sub.set_listener(motor_sub.reader_);

    // Initialise the publisher
    tof_publisher.initialise();
    std::cout << "ToF Publisher running..." << std::endl;
    tof_publisher.publishData();

   

    getchar();

    return 0;
}
