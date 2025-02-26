/**
 * @file BasePublisher.hpp
 * @author Felicity Lipscomb
 * @brief Parent Class for Publisher classes.
 * @version 0.1
 * @date 2025-02-26
 * 
 * @copyright Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
 * Referenced from FastDDS application tutorial.
 * 
 */
#ifndef BASE_PUBLISHER_HPP
#define BASE_PUBLISHER_HPP
// Publisher listener includes
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
    /**
     * @brief Parent class for Publisher classes.
     * 
     * @tparam TTopicName Template parameter for the message used.
     * @tparam TPubSubType Template parameter for the PubSubType.
     */
    template <typename TTopicName, typename TPubSubType>
    class BasePublisher{
        private:
            DomainParticipant* participant_ = nullptr;
            Publisher* publisher_ = nullptr;
            Topic* topic_ = nullptr;
            DataWriter* writer_ = nullptr;
            TypeSupport type_;
            PubListener listener_;

        public:
            /**
             * @brief Construct a new BasePublisher object
             * 
             * @param topic_name name of the topic
             */
            BasePublisher(const std::string& topic_name):type_(new TPubSubType());
            virtual ~BasePublisher();
            bool publish(TTopicName& message);

    };
}

#endif //BASE_PUBLISHER_HPP