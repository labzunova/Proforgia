#include "Connection_loop.h"
#include <utility>
#include "boost/bind.hpp"

void Connection_loop::push_back(std::map<std::string, std::string> data, boost::asio::ip::tcp::socket &socket_  )
{
    Event new_connection = Event( std::move(data), std::move( socket_) );
    connections.push(new_connection);
}

Connection_loop::Event Connection_loop::pop_front() {
    Event front = connections.front();
    connections.pop();
    return front;
}

int Connection_loop::is_empty() {
    return connections.empty();
}

