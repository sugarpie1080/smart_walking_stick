
#include "MockMotor.hpp"
#include <iostream>
namespace smart_stick {


MockMotor::MockMotor() : BaseSubscriber("MotorCommandsTopic") {}

void MockMotor::set_listener(DataReader* reader) {
    reader->set_listener(&listener_);
}

// Callback implementation
void MockMotor::MockMotorListener::on_data_available(DataReader* reader) {
    SampleInfo info;
    MotorCommands message;
    if (reader->take_next_sample(&message, &info) == ReturnCode_t::RETCODE_OK) {
        if (info.valid_data) {
            std::cout << "DutyCycle : " << message.duty_cycle()
                      << " RECEIVED." << std::endl;
        }
    }
}
}