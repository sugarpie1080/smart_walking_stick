#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <iostream>
#include <gpiod.h>
#include <unistd.h>

namespace smart_stick
{
class Sensor {
   
    public:
        Sensor(const char* chipname, int pin);
        ~Sensor();
        
        void initialise();
        virtual void getData();
        virtual void send();
        void startListening();
    protected:
        const char* chipname;
        int pin;
        struct gpiod_line* line;
        struct gpiod_chip* chip;
};
}
#endif // SENSOR_HPP
