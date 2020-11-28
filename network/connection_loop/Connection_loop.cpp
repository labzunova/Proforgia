#include "Connection_loop.h"
#include "boost/bind.hpp"


<<<<<<< HEAD
<<<<<<< HEAD
/*void Connection_loop::start( std::shared_ptr<Connection> connection )
=======
void Connection_loop::start( std::shared_ptr<Connection> connection )
>>>>>>> Very messy code. Starting to redo the queue
=======
/*void Connection_loop::start( std::shared_ptr<Connection> connection )
>>>>>>> server is compilling and starts but does nothing
{
    //  добавить коннект в вектор и запустить
   // Event event = new Event(s)
   // connections.push_back(connection); // в примере тут был insert с одним параметром(как?),TODO разобраться
    connection->start();
}

void Connection_loop::stop( std::shared_ptr<Connection> connection )
{
    //  убрать коннект из вектора и остановить
   // connections.erase(connection);
    //connection->get_socket().close();
}

void Connection_loop::stop_all()
{
    // остановить все коннекты и очистить вектор
    for( int i= 0; i < connections.size(); i++ )
        connections.at(i)._client.stop();
   // std::for_each(connections.begin(), connections.end(), boost::bind(&Connection::stop(), _1));
    connections.clear();
<<<<<<< HEAD
<<<<<<< HEAD
}*/
=======
}
>>>>>>> Very messy code. Starting to redo the queue
=======
}*/
>>>>>>> server is compilling and starts but does nothing
