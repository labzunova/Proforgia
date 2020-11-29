#include "Connection_loop.h"

#include <utility>
#include "boost/bind.hpp"

void Connection_loop::push_back(std::map<std::string, std::string> data, std::function<void(int)> callback)
{
    Event new_connection = Event( std::move(data) );
    set_callback( &new_connection, callback );
    connections.push(new_connection);
}

void Connection_loop::set_callback(Connection_loop::Event *event, std::function<void(int)> callback) {
    event->callback = std::move(callback);
}

Connection_loop::Event Connection_loop::pop_front() {
    Event front = connections.front();
    connections.pop();
    return front;
}

int Connection_loop::get_size() {
    return connections.size();
}
