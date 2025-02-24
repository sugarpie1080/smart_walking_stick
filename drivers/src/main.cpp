#include <tof_sensor.hpp>

int main() {
    // Create an object inside the SensorLib namespace
    // smart_stick::ToFSensor tempSensor("/dev/gpiochip0", 16);
    smart_stick::ToFSensor tempSensor("/dev/gpiochip0",17);
    // Initialize and start listening for interrupts
    tempSensor.initialise();
    tempSensor.startListening();

    return 0;
}
