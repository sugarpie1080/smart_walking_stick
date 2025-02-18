
#include <tof_sensor.hpp>
// Driver Includes
#include <VL53L0X.hpp>


namespace smart_stick 
{
    ToFSensor::ToFSensor(const char* chipname, int line): Sensor(chipname, line) {}

    void ToFSensor::initialise()
    {
        sensor.initialize();
    }
    
    void ToFSensor::getData()
    {
        
        std::cout << "Reading Distance data..." << std::endl;
        // For now, simulate getting data
        uint16_t distance = sensor.readRangeSingleMillimeters();

        std::cout << "Distance: " << distance << "mm" << std::endl;
    }
    
    void ToFSensor::send() {
        std::cout << "Sending Distance data..." << std::endl;
    }
}