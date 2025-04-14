#include <iostream>
#include <zmq.hpp>
#include "logzmq.h"

template <typename T>
Publisher<T>::Publisher(const std::string& address) :
    m_address{address},
    m_context{1}
{
    m_publisher = zmq::socket_t{m_context, ZMQ_PUB};
    m_publisher.bind(m_address);
}

template <typename T>
void Publisher<T>::publish(T number)
{
    zmq::message_t message(sizeof(T));
    memcpy(message.data(), &number, sizeof(T));
    m_publisher.send(message, zmq::send_flags::dontwait);
}

template<typename T>
void Publisher<T>::publish(T* numbers, size_t size)
{
    zmq::message_t message(sizeof(T) * size);
    memcpy(message.data(), numbers, sizeof(T)*size);
    m_publisher.send(message, zmq::send_flags::dontwait);
}

template<typename T>
void Publisher<T>::publish(const std::vector<T>& numbers)
{
    zmq::message_t message(sizeof(T) * numbers.size());
    memcpy(message.data(), numbers.data(), sizeof(T)* numbers.size());
    m_publisher.send(message, zmq::send_flags::dontwait);
}


template<typename T>
Subscriber<T>::Subscriber(const std::string& address) :
    m_address{address},
    m_context{1}
{
    m_subscriber = zmq::socket_t(m_context, zmq::socket_type::sub);
    m_subscriber.connect(m_address);
    m_subscriber.set(zmq::sockopt::subscribe, "");
}

template<typename T>
std::vector<T> Subscriber<T>::subscribe()
{
    zmq::message_t update;
    const auto opt_size = m_subscriber.recv(update, zmq::recv_flags::none);

    if (!opt_size.has_value())
    {
        std::cerr << "Error occured at recv!\n";
        return std::vector<T>();
    }

    std::vector<T> output(opt_size.value() / (sizeof(T)));
    std::memcpy(output.data(), update.data(), opt_size.value());

    return output;
}

template<typename T>
size_t Subscriber<T>::subscribe(T* buffer)
{
    zmq::message_t update;
    const auto opt_size = m_subscriber.recv(update, zmq::recv_flags::none);

    if (!opt_size.has_value())
    {
        std::cerr << "Error occured at recv!\n";
        return 0;
    }

    std::memcpy(buffer, update.data(), opt_size.value());
    return opt_size.value();
}


template class Publisher<float>;
template class Publisher<double>;
template class Subscriber<float>;
template class Subscriber<double>;
