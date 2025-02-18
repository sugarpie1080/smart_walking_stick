#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <iostream>
#include <gpiod.h>
#include <unistd.h>

namespace smart_stick
{
class Sensor {
    protected:
        const char* chipname;
        int pin;
        struct gpiod_line* line;
        struct gpiod_chip* chip;
    public:
        Sensor(const char* chipname, unsigned int line);
        ~Sensor();
        
        void initialise();
        void getData();
        void send();
        void startListening();

};
}
#endif // SENSOR_HPP
