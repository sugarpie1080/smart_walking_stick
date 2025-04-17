#ifndef BATTERY_HPP
#define BATTERY_HPP

#include <INA219.hpp>
#include <mutex>
#include <thread>
#include <atomic>
#include <condition_variable>

namespace smart_stick {

class Battery {
public:
    struct CallbackInterface {
        virtual void has_battery(int battery_percentage) = 0;
    };

    Battery();
    ~Battery();

    void initialise();  // Initialize the INA219 sensor
    void start();       // Start monitoring battery data
    void stop();        // Stop monitoring battery data
    void register_callback(CallbackInterface* ci);

private:
    void worker();  // Background thread for monitoring battery data

    INA219 ina219;  // INA219 driver object
    std::vector<CallbackInterface*> callbackInterfaces;

    std::mutex mutex;
    std::condition_variable cv;
    std::thread worker_thread;
    std::atomic_bool running;
};

}  // namespace smart_stick

#endif // BATTERY_HPP