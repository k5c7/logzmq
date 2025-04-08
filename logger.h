#ifndef LOGGER_H
#define LOGGER_H
#include <string>
#include <zmq.hpp>

template <typename T>
class Logger
{
public:
    explicit Logger(const std::string& address);
    void log(T number);
    void log(T* numbers, size_t size);
    void log(const std::vector<T>& numbers);

private:
    const std::string m_address;
    zmq::context_t m_context;
    zmq::socket_t m_publisher;
};

#endif // LOGGER_H
