
#include "MotorMove.hpp"
#include <iostream>
namespace smart_stick {


MotorMove::MotorMove() : BaseSubscriber("MotorCommandsTopic") 
{
    chip = gpiod_chip_open(chipname);
    // Check if can be opened
    if (!chip) {
        std::cerr << "Failed to open GPIO chip!" << std::endl;
        exit(1);
    }
    // Get the GPIO line
    line = gpiod_chip_get_line(chip, pin);
    if (!line) {
        std::cerr << "Failed to get GPIO line!" << std::endl;
        gpiod_chip_close(chip);
        exit(1);
    }

    int ret = gpiod_line_request_output(line,"Consumer",0);
}

void MotorMove::set_listener(DataReader* reader) {
    reader->set_listener(&listener_);
}

// Callback implementation
void MotorMove::MotorMoveListener::on_data_available(DataReader* reader) {
    struct gpiod_line* line = parent_->getLine();
    SampleInfo info;
    MotorCommands message;
    if (reader->take_next_sample(&message, &info) == ReturnCode_t::RETCODE_OK) {
        if (info.valid_data) {
           if (message.duty_cycle() == 100) {
                // To be Changed with the actual motor command
               std::cout << "Full Power!" << std::endl;
            //    gpiod_line_set_value(1); 
           } else {
                // To be Changed with the actual motor command
               std::cout << "Motor Off" << std::endl;
           }
        }
    }
}
}