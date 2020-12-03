#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "Connection.h"

using std::string;

Connection::Connection(boost::asio::io_service &io_service, Connection_queue &loop ):
        socket_( io_service ),
        connection_queue(loop )
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
}

void Connection::stop()
{
    socket_.close();
}

void Connection::handle_read( const Connection::error_code &e, std::size_t bytes_transferred )
{
    /* boost::asio::async_write(socket_, boost::asio::buffer(buffer_), // это тут было для тестирования эхо-сервера, пусть пока побудет
                             boost::bind(&Connection::handle_write, shared_from_this(),boost::asio::placeholders::error)); */

    Request request( std::string(buffer_.begin(), buffer_.end() ) ); // внутри реквеста вызывается парсер и записывает в поля реквеста готовые значения

    std::map<string, string> to_put_in_loop;  // эта мапа передается в воркеры для обработки апи
    if ( request.get_method() == "GET" )
        to_put_in_loop.insert(std::pair<string, string>("method","GET"));
    else
        to_put_in_loop.insert(std::pair<string, string>("method","POST"));

    if ( request.get_action() == "MAIN") // так будет записываться после парсинга случай, когда нужно получить главную страницу
    {
        to_put_in_loop.insert(std::pair<string, string>("action","GET"));
        to_put_in_loop.insert(std::pair<string, string>("session",request.get_cookie("session")));
    }

    if ( request.get_action() == "LOGIN_GET") // получить страницу входа
        to_put_in_loop.insert(std::pair<string, string>("action","LOGIN"));
    if ( request.get_action() == "LOGIN_POST") // залогинить пользователя+вернуть гланую
    {
        to_put_in_loop.insert(std::pair<string, string>("action","LOGIN"));
        to_put_in_loop.insert(std::pair<string, string>("login",request.get_data("login")));
        to_put_in_loop.insert(std::pair<string, string>("password",request.get_data("password")));
    }

    if ( request.get_action() == "SIGNUP_GET") // получить страницу регистрации
        to_put_in_loop.insert(std::pair<string, string>("action","SIGNUP"));
    if ( request.get_action() == "SIGNUP_POST") // зарегать пользователя+вернуть гланую
    { // зарегать пользователя = создать пользователя + добавить его в коммнату room, если она существует, иначе - создать новую комнату
        to_put_in_loop.insert(std::pair<string, string>("action","SIGNUP"));
        to_put_in_loop.insert(std::pair<string, string>("login",request.get_data("login")));
        to_put_in_loop.insert(std::pair<string, string>("password",request.get_data("password")));
        to_put_in_loop.insert(std::pair<string, string>("room",request.get_data("room")));
    }

    if ( request.get_action() == "FILES_BY_TAG") // получить главную страницу со списком файлов по желаемому тегу
    {
        to_put_in_loop.insert(std::pair<string, string>("action","FILES_BY_TAG"));
        to_put_in_loop.insert(std::pair<string, string>("tag",request.get_data("tag")));
        to_put_in_loop.insert(std::pair<string, string>("session",request.get_cookie("session"))); // чтобы проверить сессию
    }
    if ( request.get_action() == "ADD_FILE") // добавить файл с указанным тегом и вернуть ту же главную страницу
    {
        to_put_in_loop.insert(std::pair<string, string>("action","ADD_FILE"));
        to_put_in_loop.insert(std::pair<string, string>("tag",request.get_data("tag")));
        to_put_in_loop.insert(std::pair<string, string>("session",request.get_cookie("session")));
        //to_put_in_loop.insert(std::pair<string, string>("file",request.get_data("file"))); TODO!!!!! тут будет добавка файла но надо разобраться как
    }

    connection_queue.push_back(to_put_in_loop, socket_ ); // пихаем в очередь мапу и сокет для колбэка: моя обработка данного запроса окончена, отправит уже колбэк
}

void Connection::callback_to_write(std::array<char, 8192> buffer) {
    boost::asio::async_write(socket_, boost::asio::buffer(buffer),
                             boost::bind(&Connection::handle_write, shared_from_this(),boost::asio::placeholders::error));
}

void Connection::handle_write( const Connection::error_code &e )
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
       // connection_queue.stop(shared_from_this());
    }
}




