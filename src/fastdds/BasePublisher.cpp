
#include <ToFDataPublisher.hpp>

namespace smart_stick
{
    BasePublisher(const std::string& topic_name): : type_(new TPubSubType())
    {
        DomainParticipantQos participantQos;
        participantQos.name("Participant_publisher");
        participant_ = DomainParticipantFactory::get_instance()->create_participant(0, participantQos);

        if (participant_ == nullptr)
        {
            throw std::runtime_error("Failed to create DomainParticipantQos");;
        }

        // Register the Type
        type_.register_type(participant_);
        
        // Create the publications Topic
        topic_ = participant_->create_topic(topic_name,type_.get_type_name(),TOPIC_QOS_DEFAULT);

        if (topic_ == nullptr)
        {
            throw std::runtime_error("Failed to create Topic");

        }

        // Create the Publisher
        publisher_ = participant_->create_publisher(PUBLISHER_QOS_DEFAULT, nullptr);

        if (publisher_ == nullptr)
        {
            throw std::runtime_error("Failed to create Topic");
        }

        // Create the DataWriter
        writer_ = publisher_->create_datawriter(topic_, DATAWRITER_QOS_DEFAULT, &listener_);

         if (writer_ == nullptr)
         {
           throw std::runtime_error("Failed to create Publisher");
         }
     }
    }

    }

    virtual ~BasePublisher()
    {
        if (writer_ != nullptr)
        {
            publisher_->delete_datawriter(writer_);
        }
        if (publisher_ != nullptr)
        {
            participant_->delete_publisher(publisher_);
        }
        if (topic_ != nullptr)
        {
            participant_->delete_topic(topic_);
        }
        DomainParticipantFactory::get_instance()->delete_participant(participant_);
    
    }

    bool BasePublisher::publish(T& message)
    {
        if (listener_.matched_ > 0)
        {
            writer_->write(&message);
            return true;
        }
        return false;   
    }
    
        

    
}