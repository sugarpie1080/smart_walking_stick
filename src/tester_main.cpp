#include <tof_sensor.hpp>
#include <MotorMove.hpp>
#include <iostream>
#include <thread>
#include <chrono>


int main(int argc, char *argv[]) {
	const char*  chipname = "/dev/gpiochip0";  
    int line = 17; 
    smart_stick::ToFSensor tof(chipname,17);
    smart_stick::MotorMove mm(&tof);
    
    tof.initialise();
    tof.start();
    getchar();
    return 0;
  
}