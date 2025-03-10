/**
 * @file ToFDataPublisher.hpp
 * @author Felicity Lipscomb
 * @brief Publisher Class for ToF Data
 * @version 0.1
 * @date 2025-02-26
 * 
 */
#ifndef TOF_DATA_PUBLISHER_HPP
#define TOF_DATA_PUBLISHER_HPP

// Publisher Include
#include <BasePublisher.hpp>
// Message Type Include
#include <ToFDataPubSubTypes.h>
// Sensor Include
#include "tof_sensor.hpp"

namespace smart_stick
{
    /**
     * @brief Publisher class for ToFData messages. Derived from the BasePublisher Class.
     * 
     */
    class ToFDataPublisher : public BasePublisher<ToFData, ToFDataPubSubType>
    {
    public:
        /**
         * @brief Construct a new ToFDataPublisher object
         * 
         */
        ToFDataPublisher(const char* chipname, int line);
        
        void initialise();
        /**
         * @brief Runs the publisher loop, reading sensor data and publishing it
         * 
         */
        void run();
    private:
        /**
         * @brief ToF Sensor object
         * 
         */
        ToFSensor sensor;
    };

} // namespace smart_stick

#endif // TOF_DATA_PUBLISHER_HPP
