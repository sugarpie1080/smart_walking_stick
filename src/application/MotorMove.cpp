
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
}

// Callback implementation
void MotorMove::MotorMoveListener::on_data_available(DataReader* reader) {
    SampleInfo info;
    MotorCommands message;
    int ret;
    if (reader->take_next_sample(&message, &info) == ReturnCode_t::RETCODE_OK) {
        if (info.valid_data) {
            std::cout << "Sent Motor Command: " << message.duty_cycle() << std::endl;
            float duty_cycle = message.duty_cycle();
            parent_->pwm.setDutyCycle(duty_cycle);


        }
    }
}
}