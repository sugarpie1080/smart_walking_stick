/**
 * @file main_sub.cpp
 * @author Felicity Lipscomb
 * @brief Example subscriber entrypoint.
 * @version 0.1
 * @date 2025-02-26
 * 
 * This file shows how use can use the derived subscriber class to recieve messages.
 * This file creates a subscriber object and initialises it. It then sets the listener
 * for the subscriber and waits for the user to stop the subscriber. The listener is connected to the 
 * callback function from the ToFListenerClass, which prints the recieved message to the console.
 */
#include <ToFDataSubscriber.hpp>

int main()
{
    std::cout << "Starting subscriber. Press any key to stop it." << std::endl;
    // create a subscriber object.
    smart_stick::ToFDataSubscriber mysub;
    // initialise the subscriber.
    mysub.init();
    // set the listener for the subscriber. 
    // this to allow for the new callback function to be called.
    mysub.set_listener(mysub.reader_);

    getchar();

    return 0;
}
