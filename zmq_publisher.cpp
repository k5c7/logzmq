#include <thread>
#include <chrono>
#include "logger.h"

int main()
{
    const std::string address = "tcp://127.0.0.1:5555";
    constexpr size_t size = 100;

    Publisher<float> publisher(address);
    std::vector<float> vec(size);

    for (size_t idx = 0; idx < size; idx++)
    {
        vec[idx] = idx;
    }

    while (true)
    {
        publisher.publish(vec);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    return 0;
}
