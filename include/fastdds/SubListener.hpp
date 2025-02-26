#ifndef SUBLISTENER_HPP
#define SUBLISTENER_HPP

#include <fastdds/dds/subscriber/DataReaderListener.hpp>

using namespace eprosima::fastdds::dds;


template <typename TTopicName>
class SubListener : public DataReaderListener
    {
    public:
        SubListener() {};

        ~SubListener() override {};

        void on_subscription_matched(DataReader*,
                const SubscriptionMatchedStatus& info) override
        {
            if (info.current_count_change == 1)
            {
                std::cout << "Subscriber matched." << std::endl;
            }
            else if (info.current_count_change == -1)
            {
                std::cout << "Subscriber unmatched." << std::endl;
            }
            else
            {
                std::cout << info.current_count_change
                        << " is not a valid value for SubscriptionMatchedStatus current count change" << std::endl;
            }
        }

	// callback
        
        virtual void on_data_available(DataReader* reader)
        {
            SampleInfo info;
            TTopicName hello;
        }

    };

#endif