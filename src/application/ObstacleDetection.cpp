
#include <ObstacleDetection.hpp>
#include <iostream>
namespace smart_stick {


ObstacleDetectionSub::ObstacleDetectionSub() : BaseSubscriber("ToFDataTopic") {}

void ObstacleDetectionSub::set_listener(DataReader* reader) {
    reader->set_listener(&listener_);
}

// Callback implementation
void ObstacleDetectionSub::OSSubListener::on_data_available(DataReader* reader) {
    SampleInfo info;
    ToFData message;
    if (reader->take_next_sample(&message, &info) == ReturnCode_t::RETCODE_OK) {
        if (info.valid_data) {
            std::cout << "Distance: " << message.distance()
                      << " with time: " << message.index()
                      << " RECEIVED." << std::endl;
        }
    }
}
}