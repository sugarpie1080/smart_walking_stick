#ifndef HELLO_WORLD_SUBSCRIBER_HPP
#define HELLO_WORLD_SUBSCRIBER_HPP
#include "BaseSubscriber.hpp"
#include "HelloWorldMsgPubSubTypes.h"
#include "SubListener.hpp"
#include "HelloWorldMsg.h"

using namespace eprosima::fastdds::dds;

class HelloWorldSubscriber : public BaseSubscriber<HelloWorldMsg, HelloWorldMsgPubSubType> {
    protected:
        // Define the listener as a member of HelloWorldSubscriber
        class HelloWorldListener : public SubListener<HelloWorldMsg> {
            public:
                void on_data_available(DataReader* reader) override {
                    SampleInfo info;
                    HelloWorldMsg hello;
                    std::cout << "Yasssssssssssssssssss" << std::endl;
                    if (reader->take_next_sample(&hello, &info) == ReturnCode_t::RETCODE_OK)
                    {
                        if (info.valid_data)
                        {
                            std::cout << "Message: " << hello.message() << " with index: " << hello.index()
                                      << " RECEIVED." << std::endl;
                        }
                    }
                }
        };

        HelloWorldListener listener_;

    public:
        HelloWorldSubscriber() : BaseSubscriber("HelloWorldTopic") {}

        // Set listener_ to the DataReader
        void set_listener(DataReader* reader) {
            reader->set_listener(&listener_);
        }
};

#endif