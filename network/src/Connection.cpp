#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include <unordered_map>

#include "Connection.h"

using std::string;

Connection::Connection ( boost::asio::io_service &io_service, std::shared_ptr<Connection_queue> loop ):
        socket_( io_service ),
        connection_queue( loop )
{
}

boost::asio::ip::tcp::socket &Connection::get_socket()
{
    return socket_;
}

void Connection::start()
{
    socket_.async_read_some( boost::asio::buffer( buffer_ ),
                            boost::bind( &Connection::handle_read, shared_from_this(),
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred ) );
}

void Connection::stop()
{
    socket_.close();
}

void Connection::handle_read( const Connection::error_code &e, std::size_t bytes_transferred )
{
    /*boost::asio::async_write(socket_, boost::asio::buffer(buffer_), // это тут было для тестирования эхо-сервера, пусть пока побудет
                             boost::bind(&Connection::handle_write, shared_from_this(),boost::asio::placeholders::error));*/
    string request_( std::begin( buffer_ ), std::end( buffer_ ) );
    Request_handler request( request_ ); // внутри реквеста вызывается парсер и записывает в поля реквеста готовые значения
    std::map<string, string> to_put_in_loop = request.get_map();  // эта мапа передается в воркеры для обработки апи

    connection_queue->push_back( to_put_in_loop, socket_ ); // пихаем в очередь мапу и сокет для колбэка: моя обработка данного запроса окончена, отправит уже колбэк
}


