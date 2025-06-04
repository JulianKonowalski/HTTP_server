#pragma once

#include <iostream>

namespace server::core {

/*
 * @brief base TCPHandler class
 *  used as a functor for executing
 *  TCP client handling logic
 */
class TCPHandler {
public:

    /*
     * @brief virtual method that 
     *  prints out a debug message.
     *  Can be overriden to supply 
     *  custom client handling logic.
     */
    virtual void operator()(void) {
        std::cout << "Handling new connection\n";
    }
};

}

