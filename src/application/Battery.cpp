#include <Battery.hpp>
#include <iostream>

namespace smart_stick {

Battery::Battery() : ina219(), running(false) {}

Battery::~Battery() {
    stop();
}

void Battery::initialise() {
    ina219.initialise();  // Initialize INA219 sensor
}

void Battery::start() {
    running = true;
    worker_thread = std::thread(&Battery::worker, this);
}

void Battery::stop() {
    running = false;
    cv.notify_all();
    if (worker_thread.joinable()) {
        worker_thread.join();
    }
}

void Battery::register_callback(CallbackInterface* ci) {
    std::lock_guard<std::mutex> lock(mutex);
    callbackInterfaces.push_back(ci);
}

void Battery::worker() {
    while (running) {
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait_for(lock, std::chrono::seconds(2));  // Poll every 2 seconds

        if (!running) break;

        // Retrieve battery data using INA219
        float voltage = ina219.getBusVoltage_V();
        int battery_percentage = (voltage - 6) / (12.6 - 6) * 100;  // Example calculation
        if (battery_percentage > 100) battery_percentage = 100;
        if (battery_percentage < 0) battery_percentage = 0;

        std::cout << "Battery Voltage: " << voltage << "V, "
                  << "Percentage: " << battery_percentage << "%" << std::endl;

        // Notify callback interfaces
        for (auto cb : callbackInterfaces) {
            cb->has_battery(battery_percentage);
        }
    }
}

}  // namespace smart_stick