
#include <ToFDataPublisher.hpp>
#include <iostream>

int main() {
    const char* chipname = "/dev/gpiochip0";  // Adjust based on hardware
    int line = 17; // Adjust GPIO pin number accordingly

    smart_stick::ToFPublisher tof_publisher(chipname, line);
    tof_publisher.initialise();

    std::cout << "ToF Publisher running..." << std::endl;
    tof_publisher.publishData();
}
