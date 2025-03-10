/**
 * @file ToFDataSubscriber.cpp
 * @author Felicity Lipscomb
 * @brief Example Subscriber class.
 * @version 0.1
 * @date 2025-02-26
 * 
 * 
 */
#include "ToFDataSubscriber.hpp"
#include <iostream>
namespace smart_stick {


ToFDataSubscriber::ToFDataSubscriber() : BaseSubscriber("ToFDataTopic") {}

void ToFDataSubscriber::set_listener(DataReader* reader) {
    reader->set_listener(&listener_);
}

// Callback implementation
void ToFDataSubscriber::ToFDataListener::on_data_available(DataReader* reader) {
    SampleInfo info;
    ToFData message;
    if (reader->take_next_sample(&message, &info) == ReturnCode_t::RETCODE_OK) {
        if (info.valid_data) {
            std::cout << "Distance: " << message.distance()
                      << " with time: " << message.sec() << " seconds and " << message.nanosec() << " nanoseconds"
                      << " RECEIVED." << std::endl;
        }
    }
}
}