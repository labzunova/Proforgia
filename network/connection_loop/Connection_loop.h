#ifndef PROFORGIA_CONNECTION_LOOP_H
#define PROFORGIA_CONNECTION_LOOP_H
#include <utility>
#include <queue>
#include "Connection.h"

class Connection_loop: private boost::asio::noncopyable
{
private:
    struct Event {
        Event( std::map<std::string, std::string> data_ ): data( std::move( data_ ) ) {} // TODO by link
        std::function<void(int)> callback;
        std::map<std::string, std::string> data; // TODO maybe reference_wrapper?
    };
    void set_callback( Event * event, std::function<void(int)> callback ); // TODO good link AND TODO or callback will be the same?
    std::queue<Event> connections;
public:
    void push_back(std::map<std::string, std::string> data, std::function<void(int)> callback);
    Event pop_front();
    int get_size();
};


#endif //PROFORGIA_CONNECTION_LOOP_H
