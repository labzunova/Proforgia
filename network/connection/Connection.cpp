#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "Connection.h"

using std::string;

Connection::Connection ( boost::asio::io_service &io_service, Connection_queue &loop ):
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

   // Request request( std::string(buffer_.begin(), buffer_.end() ) ); // внутри реквеста вызывается парсер и записывает в поля реквеста готовые значения
    std::map<string, string> to_put_in_loop;  // эта мапа передается в воркеры для обработки апи
    /*if ( request.get_method() == "GET" )
    {
        string path = request.get_path();
        to_put_in_loop.insert( std::pair<string, string>("path", path ) );
        to_put_in_loop.insert( std::pair<string, string>( "method","GET" ) );
        if ( path.find("main/" ) != -1 ) // тут может быть, к примеру, main/first
        { // так будет записываться после парсинга случай, когда нужно получить главную страницу
            to_put_in_loop["path"] = "main";
            to_put_in_loop.insert( std::pair<string, string>( "room", request.get_room() ) );
            to_put_in_loop.insert( std::pair<string, string>( "session",request.get_cookie(( string & ) "session" ) ) );
        }
        if ( path == "rooms" ) // получить список комнат пользователя
        {
            to_put_in_loop.insert( std::pair<string, string>("path", path ) );
            to_put_in_loop.insert( std::pair<string, string>( "session",request.get_cookie(( string & ) "session" ) ) ); // чтобы проверить сессию
        }
        if ( path == "maintag" ) // получить главную страницу со списком файлов по желаемому тегу
        { // TODO: tag
            to_put_in_loop.insert( std::pair<string, string>("path", path ) );
            to_put_in_loop.insert( std::pair<string, string>( "tag",request.get_data( ( string & ) "tag" ) ) );
            to_put_in_loop.insert(std::pair<string, string>("session",request.get_cookie(( string & ) "session" ) ) ); // чтобы проверить сессию
        }

    }
    else
    {
        to_put_in_loop.insert( std::pair<string, string>( "method","POST" ) );
        string path = request.get_path();
        to_put_in_loop.insert( std::pair<string, string>("path", path ) );
        if ( path == "login") // залогинить пользователя+вернуть страницу выбора его комнат
        {
            to_put_in_loop.insert( std::pair<string, string>( "login",request.get_data( ( string & ) "login" ) ) );
            to_put_in_loop.insert( std::pair<string, string>( "password",request.get_data( ( string & ) "password" ) ) );
        }
        if ( path == "signup" ) // зарегать пользователя+вернуть страницу выбора его комнат
        {
            to_put_in_loop.insert(std::pair<string, string>( "login",request.get_data( ( string & ) "login" ) ) ) ;
            to_put_in_loop.insert(std::pair<string, string>( "mail",request.get_data( ( string & ) "mail" ) ) ) ;
            to_put_in_loop.insert(std::pair<string, string>( "password",request.get_data( ( string & ) "password" ) ) );
        }
        if ( path == "addpost" ) // добавить файл с указанным тегом и вернуть ту же главную страницу
        { // TODO: room
            to_put_in_loop.insert( std::pair<string, string>( "tag",request.get_data( ( string & ) "tag" ) ) );
            to_put_in_loop.insert( std::pair<string, string>( "fileurl",request.get_data( ( string & ) "fileurl" ) ) );
            to_put_in_loop.insert( std::pair<string, string>( "session",request.get_cookie( ( string & ) "session" ) ) );
        }
        if ( path == "room" ) // вступить в новую комнату и вернуть ее
        {
            to_put_in_loop.insert( std::pair<string, string>( "tag",request.get_data( ( string & ) "room" ) ) );
            to_put_in_loop.insert( std::pair<string, string>( "session",request.get_cookie( ( string & ) "session" ) ) );
        }
    }*/
    connection_queue.push_back( to_put_in_loop, socket_ ); // пихаем в очередь мапу и сокет для колбэка: моя обработка данного запроса окончена, отправит уже колбэк
}

void Connection::callback_to_write( std::array<char, 8192> buffer ) {
    boost::asio::async_write( socket_, boost::asio::buffer( buffer ),
                             boost::bind( &Connection::handle_write, shared_from_this(), boost::asio::placeholders::error ) );
}

void Connection::handle_write( const Connection::error_code &e )
{
    // выполняющаяся при чтении функция, которая биндится при запуске асинхронного чтения
    if (!e)
    {
        // Initiate graceful connection closure.
        boost::system::error_code ignored_ec;
        socket_.shutdown( boost::asio::ip::tcp::socket::shutdown_both, ignored_ec );
    }

    if ( e != boost::asio::error::operation_aborted  )
    {
       // connection_queue.stop(shared_from_this());
    }
}




