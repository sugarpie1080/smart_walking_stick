
#include <ToFDataPublisher.hpp>

namespace smart_stick
{
    ToFDataPublisher() : type_(new ToFDataPubSubTypes());

    ~ToFDataPublisher()
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
    
}