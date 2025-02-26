/**
 * @file ToFDataPublisher.hpp
 * @author Felicity Lipscomb
 * @brief Example Publisher Class
 * @version 0.1
 * @date 2025-02-26
 * 
 * 
 */
#ifndef TOF_DATA_PUBLISHER_HPP
#define TOF_DATA_PUBLISHER_HPP

// Publisher Include
#include <BasePublisher.hpp>
// Message Type Include
#include <ToFDataPubSubTypes.h>

namespace smart_stick
{
    /**
     * @brief Example Publisher class for ToFData messages. Derived from the BasePublisher Class.
     * 
     * To use the base example, you must declare the class 
     * with the message type and the PubSubType.
     */
    class ToFDataPublisher : public BasePublisher<ToFData, ToFDataPubSubType> {
    public:
        /**
         * @brief Construct a new ToFDataPublisher object
         * 
         */
        ToFDataPublisher();
    };

} // namespace smart_stick

#endif // TOF_DATA_PUBLISHER_HPP
