/**
 * @file SubListener.hpp
 * @author Felicity Lipscomb
 * @brief This file contains the class for determining if a subscriber has a matching publisher.
 * @version 0.1
 * @date 2025-02-26
 * 
 * This file contains the class for determining if a subscriber has a matching publisher. 
 * It also contains the callback function for the subscriber, which determines what actions
 * are taken with the message from the subscriber.
 * 
 * @copyright Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
 * Referenced from FastDDS application tutorial.
 */
#ifndef SUBLISTENER_HPP
#define SUBLISTENER_HPP

#include <fastdds/dds/subscriber/SampleInfo.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>

using namespace eprosima::fastdds::dds;

/**
 * @brief Class for determining if a subscriber has a matching publisher.
 * 
 * @tparam TTopicName Template parameter for the message used. 
 */
template <typename TTopicName>
class SubListener : public DataReaderListener
    {
    public:
        /**
         * @brief Construct a new SubListener object
         * 
         */
        SubListener() {};
        /**
         * @brief Destroy the SubListener object
         * 
         */
        ~SubListener() override {};
        /**
         * @brief Determines if the subscriber has a matching publisher.
         * 
         * @param info A structure for storing the matching status of the subsctriber.
         */
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
        /**
         * @brief Callback function for the subscriber.
         * 
         * @param reader The DataReader object.
         */        
        virtual void on_data_available(DataReader* reader)
        {
            SampleInfo info;
            TTopicName hello;
        }

    };

#endif