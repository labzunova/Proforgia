<<<<<<< HEAD
#include "Connection.h"
#include "../parser/Parser.h"
#include <boost/asio.hpp>
#include <iostream>
#include "boost/bind.hpp"

Connection::Connection( boost::asio::io_service &io_service, Connection_loop &loop ):
socket_( io_service ),
connection_loop( loop )
{
}

boost::asio::ip::tcp::socket &Connection::get_socket()
{
    return socket_;
}

void Connection::start()
{
    socket_.async_read_some(boost::asio::buffer(buffer_),
                            boost::bind(&Connection::handle_read, shared_from_this(),
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));
    std::cout << 'im here';
}

void Connection::stop()
{
    socket_.close();
}

void Connection::handle_read( const Connection::error_code &e, std::size_t bytes_transferred )
{
    // чтение, парсинг, положить в очередь, передав callback
<<<<<<< HEAD
<<<<<<< HEAD
    boost::asio::async_write(socket_, boost::asio::buffer(buffer_),
                             boost::bind(&Connection::handle_write, shared_from_this(),
                                         boost::asio::placeholders::error));
    //std::cout << 'im here';
}

void Connection::handle_write( const Connection::error_code &e )
=======
=======
    std::cout << 'im here';
>>>>>>> server is compilling and starts but does nothing
}

/*
void Connection::do_write( const Connection::error_code &e )
>>>>>>> Very messy code. Starting to redo the queue
{
    // выполняющаяся при чтении функция, которая биндится при запуске асинхронного чтения
    if (!e)
    {
        // Initiate graceful connection closure.
        boost::system::error_code ignored_ec;
        socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
    }

    if (e != boost::asio::error::operation_aborted)
    {
<<<<<<< HEAD
       // connection_loop.stop(shared_from_this());
=======
        connection_loop.stop(shared_from_this());
>>>>>>> Very messy code. Starting to redo the queue
    }
}
*/


=======
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

void Connection::do_read( const Connection::error_code &e, std::size_t bytes_transferred )
{
    // чтение, парсинг, запуск асинхронного чтения
}

void Connection::do_write( const Connection::error_code &e )
{
    // выполняющаяся при чтении функция, которая биндится при запуске асинхронного чтения
}


>>>>>>> cascass improved
