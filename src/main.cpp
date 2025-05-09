/**
 * @file main.cpp
 * @author Felicity Lipscomb
 * @brief Main function for the smart_stick application
 * @version 0.1
 * @date 2025-04-05
 */

#include <iostream>
#include <thread>
#include <chrono>
// Application includes
#include <ToFSensor.hpp>
#include <MotorMove.hpp>
#include <DDSCommunicator.hpp>



int main(int argc, char *argv[]) {
	const char*  chipname = "/dev/gpiochip0";  
    int line = 17; 
    smart_stick::ToFSensor tof(chipname,17);
    smart_stick::MotorMove mm(&tof);
    smart_stick::DDSCommunicator dds(&tof,&mm);
    tof.initialise();
    tof.start();
    getchar();
    return 0;
  
}