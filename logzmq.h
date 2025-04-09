#ifndef LOGZMQ_H
#define LOGZMQ_H
#include <string>
#include <zmq.hpp>

template <typename T>
class Publisher
{
public:
    explicit Publisher(const std::string& address);
    void publish(T number);
    void publish(T* numbers, size_t size);
    void publish(const std::vector<T>& numbers);

private:
    const std::string m_address;
    zmq::context_t m_context;
    zmq::socket_t m_publisher;
};

template<typename T>
class Subscriber
{
public:
    explicit Subscriber(const std::string& address);
    [[nodiscard]] std::vector<T> subscribe();
    void subscribe(T* buffer);

private:
    const std::string m_address;
    zmq::context_t m_context;
    zmq::socket_t m_subscriber;
};

#endif // LOGZMQ_H
