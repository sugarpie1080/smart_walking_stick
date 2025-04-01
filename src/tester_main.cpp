#include <tof_sensor.hpp>
#include <sensors.hpp>
#include <iostream>
#include <thread>
#include <chrono>


int main(int argc, char *argv[]) {
	const char*  chipname = "/dev/gpiochip0";  
    int line = 17; 
    smart_stick::ToFSensor tof(chipname,17);
    tof.initialise();
    tof.registerCallback(&tof);
    tof.start();
    getchar();
    // while (true) {
    //     std::this_thread::sleep_for(std::chrono::seconds(1));
    // }
    return 0;
  
}