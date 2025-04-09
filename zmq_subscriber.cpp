#include <iostream>
#include <zmq.hpp>
#include "logzmq.h"

int main()
{
    const std::string address = "tcp://127.0.0.1:5555";
    Subscriber<float> subscriber(address);

    size_t counter = 0;

    while (true)
    {
        const auto vec = subscriber.subscribe();
        std::cout << counter++ << std::endl;
    }

    return 0;
}



