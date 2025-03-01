/**
 * @file main_pub.cpp
 * @author Felicity Lipscomb
 * @brief Example publisher entrypoint. 
 * @version 0.1
 * @date 2025-02-26
 * 
 * This file shows how use can use the derived publisher class to send messages.
 * This file creates a mock TOF message and sends it to the listener.
 */
#include <ToFDataPublisher.hpp>


int main()
{
    std::cout << "Starting publisher." << std::endl;

    // Number of samples to send
    uint32_t samples = 10;
    // Creates a publisher object
    smart_stick::ToFDataPublisher mypub;
    // Creates the mock message and gives the distance of 10mm.
    ToFData msg;
    msg.distance(10);
    msg.index(0);
    uint32_t samples_sent = 0;

    while (samples_sent < samples) {
        // publish the message
        if (mypub.publish(msg)) {
            samples_sent++;
            msg.index(samples_sent);
            std::cout << "Message: " << msg.distance() << " with index: " << msg.index()
                      << " SENT" << std::endl;
        } else {
            std::cout << "No messages sent as there is no listener." << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return 0;
}
