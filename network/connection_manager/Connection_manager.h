#ifndef PROFORGIA_CONNECTION_MANAGER_H
#define PROFORGIA_CONNECTION_MANAGER_H
#include <vector>
#include "../client/Connection.h"

class Connection_manager: private boost::asio::noncopyable
{
public:
    void start( connection_ptr c ); // добавить connection в manager и запустить его
    void stop( connection_ptr c ); // остановить конкретный connection
    void stop_all();
private:
    std::vector<connection_ptr> connections;
};


#endif //PROFORGIA_CONNECTION_MANAGER_H
