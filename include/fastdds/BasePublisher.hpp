/**
 * @file BasePublisher.hpp
 * @author Felicity Lipscomb
 * @brief Parent Class for Publisher classes.
 * @version 0.1
 * @date 2025-02-26
 * 
 * This file contains the parent class for Publisher classes. 
 * This uses templating to allow for different topics to be used,
 * and to allow for different types of messages to be sent. This hides 
 * the boilerplate code from the application layer. 
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
         * @param topic_name name of the topic.
         */
        BasePublisher(const std::string& topic_name):type_(new TPubSubType())
        {
            DomainParticipantQos participantQos;
            participantQos.name("Participant_publisher");
            participant_ = DomainParticipantFactory::get_instance()->create_participant(0, participantQos);
            if (participant_ == nullptr)
                throw std::runtime_error("Failed to create DomainParticipant");
    
            type_.register_type(participant_);
            topic_ = participant_->create_topic(topic_name,type_.get_type_name() , TOPIC_QOS_DEFAULT);
            if (topic_ == nullptr)
                throw std::runtime_error("Failed to create Topic");
            
            publisher_ = participant_->create_publisher(PUBLISHER_QOS_DEFAULT, nullptr);
            if (publisher_ == nullptr)
                throw std::runtime_error("Failed to create Publisher");
            
                writer_ = publisher_->create_datawriter(topic_, DATAWRITER_QOS_DEFAULT, &listener_);
            if (writer_ == nullptr)
                throw std::runtime_error("Failed to create Reader");
        }
        
        /**
         * @brief Destroy the BasePublisher object
         * 
         */
        virtual ~BasePublisher()
        {
            if (writer_ != nullptr)
                publisher_->delete_datawriter(writer_);
            if (publisher_ != nullptr)
                participant_->delete_publisher(publisher_);
            if (topic_ != nullptr)
                participant_->delete_topic(topic_);
            DomainParticipantFactory::get_instance()->delete_participant(participant_);
        }
        
        /**
         * @brief Publishes the message generated.
         * 
         * @param message message to be published.
         * @return true message sent successfully.
         * @return false message failed to send.
         */
        bool publish(TTopicName& message)
        {
            if (listener_.matched_ > 0)
            {
                writer_->write(&message);
                return true;
            }
            return false;
        }

};


#endif //BASE_PUBLISHER_HPP