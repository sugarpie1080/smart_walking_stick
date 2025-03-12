
#include "MotorMove.hpp"
#include <iostream>
namespace smart_stick {


MotorMove::MotorMove() : BaseSubscriber("MotorCommandsTopic") {}

void MotorMove::set_listener(DataReader* reader) {
    reader->set_listener(&listener_);
}

// Callback implementation
void MotorMove::MotorMoveListener::on_data_available(DataReader* reader) {
    SampleInfo info;
    MotorCommands message;
    if (reader->take_next_sample(&message, &info) == ReturnCode_t::RETCODE_OK) {
        if (info.valid_data) {
           if (message.duty_cycle() == 100) {
                // To be Changed with the actual motor command
               std::cout << "Full Power!" << std::endl;
           } else {
                // To be Changed with the actual motor command
               std::cout << "Motor Off" << std::endl;
           }
        }
    }
}
}