#include <BatteryMonitor.hpp>
#include <iostream>

namespace smart_stick {

BatteryMonitor::BatteryMonitor()
    : ina219(0.1f, 3.2f, 0x40), running(false) {}

BatteryMonitor::~BatteryMonitor() {
    stop();
}

void BatteryMonitor::initialise() {
    // Initialize INA219
    ina219.init();
}

void BatteryMonitor::start() {
    running = true;
    worker_thread = std::thread(&BatteryMonitor::worker, this);
}

void BatteryMonitor::stop() {
    running = false;
    cv.notify_all();
    if (worker_thread.joinable()) {
        worker_thread.join();
    }
}

void BatteryMonitor::register_callback(BatteryMonitor::CallbackInterface* ci) {
    std::lock_guard<std::mutex> lock(mutex);
    callbackInterfaces.push_back(ci);
}

void BatteryMonitor::worker() {
    while (running) {
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait_for(lock, std::chrono::seconds(2));

        if (!running) break;

        // Read bus voltage from INA219
        float voltage = ina219.read_voltage();  // Bus voltage

        // Calculate battery percentage
        float percentage = ((voltage - 6.0f) / (12.6f - 6.0f)) * 100.0f;
        percentage = std::max(0.0f, std::min(100.0f, percentage));

        std::cout << "Battery Voltage: " << voltage << "V, "
                  << "Percentage: " << percentage << "%" << std::endl;

        // Notify all registered callback interfaces
        for (auto cb : callbackInterfaces) {
            cb->has_battery(percentage); // Notify battery percentage
        }
    }
}

} // namespace smart_stick
