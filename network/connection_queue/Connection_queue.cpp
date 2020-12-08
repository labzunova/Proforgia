#include <utility>

#include "boost/bind.hpp"

#include "Connection_queue.h"

void Connection_queue::push_back(std::map<std::string, std::string>& data, boost::asio::ip::tcp::socket &socket_  )
{
    queue_mutex.lock();
    Event new_connection = Event( data, socket_ );
    connections.push(std::move(new_connection));
    queue_mutex.unlock();
}

Connection_queue::Event Connection_queue::pop_front() {
    queue_mutex.lock();
    Event front = std::move(connections.front());
    connections.pop();
    queue_mutex.unlock();
    return front;
}

const int Connection_queue::is_empty() {
    //queue_mutex.lock();
    bool check = connections.empty();
   // queue_mutex.unlock();
    return check;
}

Connection_queue::Connection_queue(Connection_queue *pQueue) {

}

Connection_queue::Connection_queue() {

}

