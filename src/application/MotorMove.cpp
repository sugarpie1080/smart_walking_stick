
#include "MotorMove.hpp"
#include <iostream>
#include <fstream>

#include <rpi_pwm.h>


namespace smart_stick {


MotorMove::MotorMove() : BaseSubscriber("MotorCommandsTopic"), listener_(this) {

    pwm.start(2,100);

}

void MotorMove::set_listener(DataReader* reader) {
    reader->set_listener(&listener_);
    motor_thread_ = std::thread([this]() {
        while (!stop_flag_) {
            // You can use a condition variable or check for data availability here
            // This loop is where the subscriber works in the background.
            // std::this_thread::sleep_for(std::chrono::milliseconds(1)); // To avoid high CPU usage in the loop
        }
    });
}

void MotorMove::stop()
{
    stop_flag_ = true;
    if (motor_thread_.joinable()) {
        motor_thread_.join(); // Wait for the thread to finish
    }
    // Shut down PWM
    pwm.stop();
}

// Callback implementation
void MotorMove::MotorMoveListener::on_data_available(DataReader* reader) {
    SampleInfo info;
    MotorCommands message;
    if (reader->take_next_sample(&message, &info) == ReturnCode_t::RETCODE_OK) {
        if (info.valid_data) {
            std::cout << "Sent Motor Command: " << message.duty_cycle() << std::endl;
            float duty_cycle = message.duty_cycle();
            parent_->pwm.setDutyCycle(duty_cycle);
        }
    }
}
}