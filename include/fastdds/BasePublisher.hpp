#ifndef BASE_PUBLISHER_HPP
#define BASE_PUBLISHER_HPP
// Pub listender includes
#include <PubListener.hpp>
// FastDDS includes
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>

#include <atomic>
#include <iostream>


using namespace eprosima::fastdds::dds;

namespace smart_stick 
{
    template <typename T, typename TPubSubType>
    class BasePublisher{
        private:
            DomainParticipant* participant_ = nullptr;
            Publisher* publisher_ = nullptr;
            Topic* topic_ = nullptr;
            DataWriter* writer_ = nullptr;
            TypeSupport type_;
            PubListener listener_;

        public:
            BasePublisher(const std::string& topic_name):type_(new TPubSubType());
            virtual ~BasePublisher();
            bool publish(T& message);

    };
}

#endif //BASE_PUBLISHER_HPP