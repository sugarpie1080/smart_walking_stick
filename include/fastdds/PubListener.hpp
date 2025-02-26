/**
 * @file PubListener.hpp
 * @author Felicity Lipscomb
 * @brief Class for determining if a publisher has a matching subscriber.
 * @version 0.1
 * @date 2025-02-25
 * 
 * 
 * @copyright Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
 * Referenced from FastDDS application tutorial.
 * 
 */
#ifndef PUBLISTENER_HPP
#define PUBLISTENER_HPP

#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <atomic>
#include <iostream>

using namespace eprosima::fastdds::dds;

/**
 * @class PubListener
 * 
 */
class PubListener : public DataWriterListener
{
public:
    std::atomic_int matched_;

    PubListener() : matched_(0) {}

    void on_publication_matched(DataWriter*, const PublicationMatchedStatus& info) override
    {
        if (info.current_count_change == 1)
        {
            matched_ = info.total_count;
            std::cout << "Publisher matched." << std::endl;
        }
        else if (info.current_count_change == -1)
        {
            matched_ = info.total_count;
            std::cout << "Publisher unmatched." << std::endl;
        }
        else
        {
            std::cout << info.current_count_change
                      << " is not a valid value for PublicationMatchedStatus current count change." << std::endl;
        }
    }
};

#endif // PUBLISTENER_HPP
