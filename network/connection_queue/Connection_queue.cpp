#include <utility>

#include "boost/bind.hpp"

#include "Connection_queue.h"

void Connection_queue::push_back(std::map<std::string, std::string> data, boost::asio::ip::tcp::socket &socket_  )
{
    queue_mutex.lock();
    Event new_connection = Event( std::move(data), std::move( socket_) );
    connections.push(new_connection);
    queue_mutex.unlock();
}

Connection_queue::Event Connection_queue::pop_front() {
    queue_mutex.lock();
    Event front = connections.front();
    connections.pop();
    queue_mutex.unlock();
    return front;
}

const int Connection_queue::is_empty() {
    return connections.empty();
}

