#ifndef PROFORGIA_CONNECTION_LOOP_H
#define PROFORGIA_CONNECTION_LOOP_H
#include <vector>
#include "Connection.h"

class Connection_loop: private boost::asio::noncopyable
{
public:
    void start( std::shared_ptr<Connection> connection ); // добавить connection в manager и запустить его
    void stop( std::shared_ptr<Connection> connection ); // остановить конкретный connection
    void stop_all();
private:
    struct Event {
        Event(/* Connection c,*/ std::string &data): /*_client(c),*/ _data(data) {}
        //Connection _client; // WANT_READ, WANT_WRITE
        std::function<void(int)> _callback;
        std::reference_wrapper<std::string> _data; // read or write buffer
    };
    std::vector<Event> connections;
};


#endif //PROFORGIA_CONNECTION_LOOP_H
