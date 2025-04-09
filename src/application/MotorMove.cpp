
#include <MotorMove.hpp>
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

void MotorMove::has_distance(float distance) {
    {
        // std::cout << "MOTOR MOVE RECIEVDD: " << distance << std::endl;
        std::unique_lock<std::mutex> lock(mutex);
        this->distance = distance;
    }  
    cv.notify_all();
}

int MotorMove::convert_distance_to_duty_cycle(float distance)
{
     
     // Ignore any 0 distance measurements (avoiding flickering)
     if (distance == 0) 
     {
        return 0;  // Return maximum PWM if distance is 0
     }
     else if (distance <= DISTANCE_MIN) 
     {
        return PWM_MAX;  // Return maximum PWM if distance is greater than threshold
     }
     else if (distance >= DISTANCE_MAX)
     {
        return 0;  // Return minimum PWM if distance is less than threshold
     }
     else 
     {  
        // Apply exponential decay scaling to the distance
        float pwm = PWM_MAX / exp((distance-DISTANCE_MIN) / DECAY_FACTOR);
        
        // Ensure PWM stays within the 0-100 range
        if (pwm < 0) pwm = 0;
        if (pwm > PWM_MAX) pwm = PWM_MAX;
        
        // Return the PWM value
        return static_cast<int>(pwm);
     }

     

}

 void MotorMove::register_callback(CallbackInterface* ci)
 {
    std::lock_guard<std::mutex> lock(mutex);
    callbackInterfaces.push_back(ci);
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
            std::cout << "MOTOR MOVE: " << distance << " PWM " << duty_cycle << std::endl;
            pwm.setDutyCycle(duty_cycle); 
            for (auto cb: callbackInterfaces)
            {
                cb->has_duty(duty_cycle);
            }
        }
        
    }
}


MotorMove::~MotorMove() 
{
    pwm.stop();
    running = false;
    cv.notify_all();
    motor_thread.join();
}

}