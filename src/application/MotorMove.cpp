
#include "MotorMove.hpp"
#include <iostream>
#include <fstream>


#define PWM_SYSFS "/sys/class/pwm/pwmchip0/"
#define PWM_PATH0 "/sys/class/pwm/pwmchip0/pwm0/"

namespace smart_stick {


MotorMove::MotorMove() : BaseSubscriber("MotorCommandsTopic"), listener_(this) {
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

    // Export PWM Channel
    writeSys(PWM_SYSFS "export", "0");
}

void MotorMove::set_listener(DataReader* reader) {
    reader->set_listener(&listener_);
}

void MotorMove::writeSys(std::string filename, std::string value) {
    std::ofstream file;
    file.open(filename);
    file << value;
    file.close();
}
// Callback implementation
void MotorMove::MotorMoveListener::on_data_available(DataReader* reader) {
    struct gpiod_line* line = parent_->getLine();
    SampleInfo info;
    MotorCommands message;
    int ret;
    if (reader->take_next_sample(&message, &info) == ReturnCode_t::RETCODE_OK) {
        if (info.valid_data) {
            // Write the motor command to the PWM file
            parent_->writeSys(PWM_PATH0 "period", "1000000");
            parent_->writeSys(PWM_PATH0 "duty_cycle", std::to_string(message.duty_cycle()));
            parent_->writeSys(PWM_PATH0 "enable", "1");
            std::cout << "Sent Motor Command: " << message.duty_cycle() << std::endl;
        //    if (message.duty_cycle() == 100) {
        //         // To be Changed with the actual motor command
        //        std::cout << "Full Power!" << std::endl;
        //        ret = gpiod_line_set_value(line,1); 
        //    } else {
        //         // To be Changed with the actual motor command
        //        std::cout << "Motor Off" << std::endl;
        //        ret = gpiod_line_set_value(line,0); 
        //    }

        }
    }
}
}