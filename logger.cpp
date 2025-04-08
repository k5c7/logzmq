#include "logger.h"
#include <zmq.hpp>


template <typename T>
Logger<T>::Logger(const std::string& address) :
    m_address{address},
    m_context{1}
{
    m_publisher = zmq::socket_t{m_context, ZMQ_PUB};
    m_publisher.bind(m_address);
}

template <typename T>
void Logger<T>::log(T number)
{
    zmq::message_t message(sizeof(T));
    memcpy(message.data(), &number, sizeof(T));
    m_publisher.send(message, zmq::send_flags::dontwait);
}

template<typename T>
void Logger<T>::log(T* numbers, size_t size)
{
    zmq::message_t message(sizeof(T) * size);
    memcpy(message.data(), numbers, sizeof(T)*size);
    m_publisher.send(message, zmq::send_flags::dontwait);
}

template<typename T>
void Logger<T>::log(const std::vector<T>& numbers)
{
    zmq::message_t message(sizeof(T) * numbers.size());
    memcpy(message.data(), numbers.data(), sizeof(T)* numbers.size());
    m_publisher.send(message, zmq::send_flags::dontwait);
}


template class Logger<float>;
template class Logger<double>;

