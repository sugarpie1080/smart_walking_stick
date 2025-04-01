#include <ToFDataPublisher.hpp>
#include <ObstacleDetection.hpp>
#include <MotorMove.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <csignal>

// Global flag to control thread execution safely
std::atomic<bool> running(true);

// Signal handler to catch Ctrl + C (SIGINT)
void signalHandler(int signum) {
    if (signum == SIGINT) {
        running = false;
    }
}

int main() {
    // Register the signal handler for SIGINT (Ctrl + C)
    std::signal(SIGINT, signalHandler);

    // Setup for DDS objects
    const char* chipname = "/dev/gpiochip0";  
    int line = 17; 
    
    smart_stick::ToFDataPublisher tof_publisher(chipname, line);
    smart_stick::ObstacleDetectionSub obstacle_sub;
    smart_stick::MotorMove motor_sub;

    // Initialise the subscriber threads
    obstacle_sub.init();
    obstacle_sub.set_listener(obstacle_sub.reader_);

    motor_sub.init();
    motor_sub.set_listener(motor_sub.reader_);

    // Initialise the publisher threads
    tof_publisher.initialise();
    std::cout << "ToF Publisher running..." << std::endl;
    tof_publisher.publishData();
    //  Main loop: checks for Ctrl+C (SIGINT) to stop the program
    while (running) {
        sleep(1);
    }

    std::cout << "Shutting down..." << std::endl;
    tof_publisher.stop();  // Stop the ToF publisher safely
    obstacle_sub.stop();
    motor_sub.stop();

    std::cout << "Clean shutdown completed." << std::endl;
    return 0;
}
