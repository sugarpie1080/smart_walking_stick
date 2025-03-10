
#include <ToFDataPublisher.hpp>
#include <ToFDataSubscriber.hpp>
#include <iostream>

int main() {
    const char* chipname = "/dev/gpiochip0";  
    int line = 17; 

    smart_stick::ToFDataPublisher tof_publisher(chipname, line);
    tof_publisher.initialise();

    smart_stick::ToFDataSubscriber mysub;
    // initialise the subscriber.
    mysub.init();
    // set the listener for the subscriber. 
    // this to allow for the new callback function to be called.
    mysub.set_listener(mysub.reader_);

    std::cout << "ToF Publisher running..." << std::endl;
    tof_publisher.publishData();

   

    getchar();

    return 0;
}
