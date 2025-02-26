#include <ToFDataPublisher.hpp>


int main()
{
    std::cout << "Starting publisher." << std::endl;
    uint32_t samples = 10;
    smart_stick::ToFDataPublisher mypub;

    ToFData msg;
    msg.distance(10);
    msg.index(0);
    uint32_t samples_sent = 0;
    while (samples_sent < samples) {
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
