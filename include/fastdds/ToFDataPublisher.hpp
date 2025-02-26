#ifndef TOF_DATA_PUBLISHER_HPP
#define TOF_DATA_PUBLISHER_HPP

#include <chrono>
#include <thread>

// Topic includes
#include <ToFDataPubSubTypes.h>
// Pub listender includes
#include <PubListener.hpp>
// FastDDS includes
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>

using namespace eprosima::fastdds::dds;

namespace smart_stick 
{
    class ToFDataPublisher{
        private:
            DomainParticipant* participant_ = nullptr;
            Publisher* publisher_ = nullptr;
            Topic* topic_ = nullptr;
            DataWriter* writer_ = nullptr;
            TypeSupport type_;
            PubListener listener_;

        public:
            ToFDataPublisher(): type_(new ToFDataPubSubTypes());
            ~ToFDataPublisher();
            bool initialisePublisher();
            bool publish();

    };
}

#endif //TOF_DATA_PUBLISHER_HPP