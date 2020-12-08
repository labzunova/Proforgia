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
    string request_( std::begin( buffer_ ), std::end( buffer_ ) );
    Request request( request_ ); // внутри реквеста вызывается парсер и записывает в поля реквеста готовые значения
    std::map<string, string> to_put_in_loop;  // эта мапа передается в воркеры для обработки апи
    if ( request.get_method() == "GET" )
    {
        to_put_in_loop.insert( std::pair<string, string>( "method","GET" ) );
        string path = request.get_path();
        if ( path == "login" || path == "signup" )
            to_put_in_loop.insert( std::pair<string, string>("path", path ) );
        if ( path == "profile" ) // получить список комнат пользователя
        {
            to_put_in_loop.insert( std::pair<string, string>("path", path ) );
            to_put_in_loop.insert( std::pair<string, string>( "session",request.get_cookie(( string & ) "session" ) ) ); // чтобы проверить сессию
        }

        if ( path.find("rooms" ) != -1 ) // тут может быть, к примеру, rooms/first
        { // так будет записываться после парсинга случай, когда нужно получить какую-то комнату или комнату с выведенными по тегу данными
            to_put_in_loop.insert( std::pair<string, string>( "room", request.get_room() ) );
            if ( request.get_tag_for_room() != "" )
            {
                to_put_in_loop["path"] = "roomtag";
                to_put_in_loop.insert( std::pair<string, string>( "tag", request.get_tag_for_room() ) );
            }
            else
                to_put_in_loop["path"] = "room";
            to_put_in_loop.insert( std::pair<string, string>( "session",request.get_cookie(( string & ) "session" ) ) );
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
        if ( path.find( "rooms" ) != -1 ) // добавить файл с указанным тегом и вернуть ту же главную страницу
        {
            to_put_in_loop["path"] = "room";
            to_put_in_loop.insert( std::pair<string, string>( "room", request.get_room() ) );
            to_put_in_loop.insert( std::pair<string, string>( "session",request.get_cookie(( string & ) "session" ) ) );
            to_put_in_loop.insert( std::pair<string, string>( "title",request.get_data( ( string & ) "title" ) ) );
            to_put_in_loop.insert( std::pair<string, string>( "tag",request.get_data( ( string & ) "tag" ) ) );
            to_put_in_loop.insert( std::pair<string, string>( "text",request.get_data( ( string & ) "text" ) ) ); // text и fileurl не обязательно будут
            to_put_in_loop.insert( std::pair<string, string>( "fileurl",request.get_data( ( string & ) "fileurl" ) ) );
        }
    }
    connection_queue.push_back( to_put_in_loop, socket_ ); // пихаем в очередь мапу и сокет для колбэка: моя обработка данного запроса окончена, отправит уже колбэк
}


