#ifndef TEST_SENSOR_H
#define TEST_SENSOR_H

#include <sensors.hpp>
// Driver Includes
#include <VL53L0X.hpp>

namespace smart_stick
{
    class ToFSensor : public Sensor
    {
        public:
            ToFSensor(const char* chipname, int line);
            void initialise() override; 
            void getData() override;
            void send() override;
        private:
            VL53L0X sensor;
    };
}

#endif


