/**
 * @file BaseSubscriber.hpp
 * @author Felicity Lipscomb
 * @brief Parent Class for Subscriber classes.
 * @version 0.1
 * @date 2025-02-26
 * 
 * This file contains the parent class for Sublisher classes. 
 * This uses templating to allow for different topics to be used,
 * and to allow for different types of messages to be recieved. This hides 
 * the boilerplate code from the application layer. 
 * 
 * @copyright Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
 * Referenced from FastDDS application tutorial.
 */
#ifndef BASE_SUBSCRIBER_HPP
#define BASE_SUBSCRIBER_HPP

// Subscriber listener includes
#include <SubListener.hpp>
// FastDDS includes
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>


using namespace eprosima::fastdds::dds;
/**
 * @brief Parent class for Subscriber classes.
 * 
 * @tparam TTopicName Template parameter for the message used.
 * @tparam TPubSubType Template parameter for the PubSubType.
 */
template <typename TTopicName, typename TPubSubType>
class BaseSubscriber
{
protected:
    DomainParticipant* participant_ = nullptr;
    Subscriber* subscriber_ = nullptr;
    Topic* topic_ = nullptr;
    TypeSupport type_;
    std::string topic_name;
public:
    DataReader* reader_ = nullptr;
    SubListener<TTopicName> listener_;

    /**
     * @brief Construct a new BaseSubscriber object
     * 
     * @param topic_name name of the topic.
     */
    BaseSubscriber(const std::string& topic_name) : type_(new TPubSubType()), topic_name(topic_name) 
    {}
    
    /**
     * @brief Initialises the Subscriber.
     * 
     */
    void init()
    {
        DomainParticipantQos participantQos;
        participantQos.name("Participant_subscriber");
        participant_ = DomainParticipantFactory::get_instance()->create_participant(0, participantQos);
    
        if (participant_ == nullptr)
            throw std::runtime_error("Failed to create DomainParticipant");
    
        type_.register_type(participant_);
        topic_ = participant_->create_topic(topic_name, type_.get_type_name(),TOPIC_QOS_DEFAULT);
        if (topic_ == nullptr)
            throw std::runtime_error("Failed to create Topic");
    
        subscriber_ = participant_->create_subscriber(SUBSCRIBER_QOS_DEFAULT, nullptr);
        if (subscriber_ == nullptr)
            throw std::runtime_error("Failed to create Publisher");
    
        reader_ = subscriber_->create_datareader(topic_, DATAREADER_QOS_DEFAULT, &listener_);
        if (reader_ == nullptr)
            throw std::runtime_error("Failed to create Reader");
    }
    /**
     * @brief Destroy the BaseSubscriber object
     * 
     */
    virtual ~BaseSubscriber()
    {
        if (reader_ != nullptr)
        {
            subscriber_->delete_datareader(reader_);
        }
        if (topic_ != nullptr)
        {
            participant_->delete_topic(topic_);
        }
        if (subscriber_ != nullptr)
        {
            participant_->delete_subscriber(subscriber_);
        }
        DomainParticipantFactory::get_instance()->delete_participant(participant_);
    }   
};

#endif // BASE_SUBSCRIBER_HPP
