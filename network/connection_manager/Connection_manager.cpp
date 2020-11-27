#include "Connection_manager.h"


void Connection_manager::start( connection_ptr c )
{
    //  добавить коннект в вектор и запустить
    connections.push_back(c); // в примере тут был insert с одним параметром(как?),TODO разобраться
    c->do_read();
}

void Connection_manager::stop( connection_ptr c )
{
    //  убрать коннект из вектора и остановить
    connections.erase(c);
    c->get_socket().close();
}

void Connection_manager::stop_all()
{
    // остановить все коннекты и очистить вектор
    for( int i= 0; i < connections.size(); i++ ) boost::bind(&Connection::stop;
   // std::for_each(connections.begin(), connections.end(), boost::bind(&Connection::stop(), _1));
    connections.clear();
}
