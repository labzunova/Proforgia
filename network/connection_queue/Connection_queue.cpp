#include <utility>

#include "boost/bind.hpp"

#include "Connection_queue.h"

void Connection_queue::push_back(std::map<std::string, std::string> data, boost::asio::ip::tcp::socket &socket_  )
{
    Event new_connection = Event( std::move(data), std::move( socket_) );
    connections.push(new_connection);
}

Connection_queue::Event Connection_queue::pop_front() {
    Event front = connections.front();
    connections.pop();
    return front;
}

int Connection_queue::is_empty() {
    return connections.empty();
}

