#include "Connection.h"
#include "../parser/Parser.h"
#include <boost/asio.hpp>

Connection::Connection( boost::asio::io_service &io_service, Connection_manager &manager, API &api_ ):
socket_( io_service ),
connection_manager( manager ),
api( api_ )
{
}

boost::asio::ip::tcp::socket &Connection::get_socket()
{
    return socket_;
}

void Connection::start()
{
    // начать асинхронное чтение
}

void Connection::stop()
{
    // закрыть сокет
}
void Connection::do_read( const Connection::error_code &e, std::size_t bytes_transferred )
{
    // чтение, парсинг, запуск асинхронного чтения
}

void Connection::do_write( const Connection::error_code &e )
{
    // выполняющаяся при чтении функция, которая биндится при запуске асинхронного чтения
}


