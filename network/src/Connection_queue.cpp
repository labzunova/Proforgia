#include <utility>

#include "boost/bind.hpp"

#include "Connection_queue.h"

void Connection_queue::push_back(std::map<std::string, std::string>& data, boost::asio::ip::tcp::socket &socket_  )
{
    const std::lock_guard<std::mutex> lock(queue_mutex);
    Event new_connection = Event( data, socket_ );
    connections.push(std::move(new_connection));
}

Connection_queue::Event Connection_queue::pop_front() {
    const std::lock_guard<std::mutex> lock(queue_mutex);
    Event front = std::move(connections.front());
    connections.pop();
    return front;
}

const int Connection_queue::is_empty() {
    const std::lock_guard<std::mutex> lock(queue_mutex);
    bool check = connections.empty();
    return check;
}

//Connection_queue::Connection_queue(Connection_queue *pQueue) {
//
//}
//
//Connection_queue::Connection_queue() {
//
//}

