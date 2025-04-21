#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <INA219.hpp>

namespace smart_stick {

/**
 * @brief Monitors battery using INA219.
 */
class BatteryMonitor {
public:
    struct CallbackInterface {
        /**
         * Callback function for when a new battery_percentage is available.
         **/
            virtual void has_battery(float battery_percentage) = 0;
        };

    BatteryMonitor();
    ~BatteryMonitor();

    void initialise();
    void start();
    void stop();
    void register_callback(CallbackInterface* ci);

private:
    void worker();

    INA219 ina219;
    bool running;
    std::thread worker_thread;
    std::mutex mutex;
    std::condition_variable cv;
    std::vector<CallbackInterface*> callbackInterfaces;
    float voltage;
    float current;
    float shunt_voltage;
    float power;
};

} // namespace smart_stick
