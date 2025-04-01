
#ifndef CALLBACK_HPP
#define CALLBACK_HPP
#include <gpiod.h>

struct CallbackInterface {
    /**
     * Called when a new sample is available.
     * This needs to be implemented in a derived
     * class by the client. Defined as abstract.
     * \param e If falling or rising.
     **/
        virtual void has_distance(gpiod_line_event& e) = 0;
    };


#endif CALLBACK_HPP