#include "ToFDataSubscriber.hpp"
#include <iostream>

ToFDataSubscriber::ToFDataSubscriber() : BaseSubscriber("ToFDataTopic") {}

void ToFDataSubscriber::set_listener(DataReader* reader) {
    reader->set_listener(&listener_);
}

// Listener implementation
void ToFDataSubscriber::ToFDataListener::on_data_available(DataReader* reader) {
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
