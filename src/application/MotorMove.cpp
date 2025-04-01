
#include "MotorMove.hpp"
#include <iostream>
#include <fstream>

#include <rpi_pwm.h>


namespace smart_stick {


MotorMove::MotorMove(ToFSensor* tof) 
{
    tof->register_callback(this);    
    pwm.start(2,100);
    running = true;
    motor_thread = std::thread(&MotorMove::worker,this);

}

MotorMove::~MotorMove() 
{
    pwm.stop();
    running = false;
    cv.notify_all();
    motor_thread.join();
}


// Callback implementation
void MotorMove::has_distance(float distance) {
    {
        std::cout << "MOTOR MOVE RECIEVDD: " << distance << std::endl;
        std::unique_lock<std::mutex> lock(mutex);
        this->distance = distance;
    }  
    cv.notify_all();
}

int MotorMove::convert_distance_to_duty_cycle(float distance)
{
     // TESTING CODE NOT ACTUAL BOUNDS
     if( distance < 200)
     {
         return 75;
     }
     else
     {
         return 25;
     }
 }

void MotorMove::worker()
{
    while(running)
    {
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock);
        if (running)
        {
            int duty_cycle = convert_distance_to_duty_cycle(distance);
            pwm.setDutyCycle(duty_cycle); 
        }
    }
}
}
