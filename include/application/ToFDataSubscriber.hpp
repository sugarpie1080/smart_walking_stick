#ifndef TOF_DATA_SUBSCRIBER_HPP
#define TOF_DATA_SUBSCRIBER_HPP

// Subscriber includes
#include <BaseSubscriber.hpp>
#include <SubListener.hpp>
#include <fastdds/dds/subscriber/SampleInfo.hpp>

// Topic includes
#include <ToFDataPubSubTypes.h>

using namespace eprosima::fastdds::dds;

class ToFDataSubscriber : public BaseSubscriber<ToFData, ToFDataPubSubType> {
protected:
    // Define the listener as a member of ToFDataSubscriber
    class ToFDataListener : public SubListener<ToFData> {
    public:
        void on_data_available(DataReader* reader) override;
    };

    ToFDataListener listener_;

public:
    // Constructor
    ToFDataSubscriber();

    // Set listener_ to the DataReader
    void set_listener(DataReader* reader);
};

#endif // TOF_DATA_SUBSCRIBER_HPP
