#include "Request_handler.h"
#include "Parser.h"

Request_handler::Request_handler( const string &request )
{
    Parser parser( request );
    method = parser.parse_method();
    path = parser.parse_path();
    if( method == "POST" )
        data = parser.parse_body();
    if( path =="delete_room" )
    {
        room = parser.parse_room_to_delete( path );
        path = "delete_room";
    }
    else if( path.find( "room/add/" ) != -1)
    {
        room = path.erase( 0, path.find('/') + 1 );
        room = room.substr( room.find('/') + 1 );
        if ( method == "GET" )
            room = room.substr( 0, room.size() - 1 ); // из-за знака ? в конце пути
        path = "add";
    }
    else if( path.find( "exit" ) != -1 )
    {
        room = path.erase( 0, path.find('/') + 1 );
        room = room.substr( room.find('/') + 1 );
        room = room.substr( 0, room.size() - 1 );
        path = "exit";
    }
    else if( path.find( "room" ) != -1 ) // если это запрос на какую-то комнату: выяснить, какую
    {
        std::pair<string, string> properties = parser.parse_room_properties( path );
        room = properties.first;
        path = "room";
        if ( properties.second != "" )
        {
            path = "roomtag";
            tag = properties.second;
        }
    }
    cookies = parser.parse_cookies();
    create_map();
}

std::map<std::string, std::string> Request_handler::get_map() const
{
    return to_put_in_loop;
}


string Request_handler::get_data( const string &type )
{
    return data[type];
}

string Request_handler::get_cookie( const string &type )
{
    return cookies[type];
}

void Request_handler::create_map()
{
    if ( method == "GET" )
    {
        if ( path == "login" )
            fill_GET_login();
        else if ( path == "signup" )
            fill_GET_signup();
        else if ( path == "profile" )// получить список комнат пользователя
            fill_GET_profile();
        else if ( path.find( "delete_room" ) != -1 )
            fill_GET_delete_room();
        else if ( path == "add" )
            fill_GET_room_adding();
        else if ( path.find( "exit" ) != -1 )
            fill_GET_exit();
        else if ( path.find("room" ) != -1 ) // тут может быть, к примеру, rooms/first
            fill_GET_room(); // случай, когда нужно получить какую-то комнату или комнату с выведенными по тегу данными
        else if ( path == "logout")
            fill_GET_logout();
    }
    else
    {
        to_put_in_loop.emplace( "path", path );
        if ( path == "login") // залогинить пользователя+вернуть страницу выбора его комнат
        {
            fill_POST_login();
        }
        if ( path == "signup" ) // зарегать пользователя+вернуть страницу выбора его комнат
        {
            fill_POST_signup();
        }
        if ( path == "add" ) // добавить файл с указанным тегом и вернуть ту же главную страницу
        {
            fill_POST_room();
        }
        if ( path == "create" ) // создать новую комнату
        {
            fill_POST_create_room();
        }
        if ( path == "join" ) // вступить в комнату
        {
            fill_POST_join_room();
        }
    }
}

void Request_handler::fill_GET_login()
{
    to_put_in_loop.emplace( "method", "GET" );
    to_put_in_loop.emplace( "path", path );
    to_put_in_loop.emplace( "session", get_cookie("session" ) );

}

void Request_handler::fill_GET_signup()
{
    to_put_in_loop.emplace( "method", "GET" );
    to_put_in_loop.emplace( "path", path );
    to_put_in_loop.emplace( "session", get_cookie("session" ) );
}

void Request_handler::fill_GET_profile()
{
    to_put_in_loop.emplace( "method", "GET" );
    to_put_in_loop.emplace( "path", path );
    to_put_in_loop.emplace( "session", get_cookie("session" ) ); // чтобы проверить сессию
}

void Request_handler::fill_GET_room()
{
    to_put_in_loop.emplace( "method", "GET" );
    to_put_in_loop.emplace( "room", room );
    if ( tag != "" )
    {
        to_put_in_loop["path"] = "roomtag";
        to_put_in_loop.emplace( "tag", tag );
    }
    else
        to_put_in_loop["path"] = "room";
    to_put_in_loop.emplace( "session", get_cookie("session" ) );
}

void Request_handler::fill_GET_room_adding()
{
    to_put_in_loop.emplace( "method", "GET" );
    to_put_in_loop.emplace( "room", room );
    to_put_in_loop.emplace( "path", "add" );
    to_put_in_loop.emplace( "session", get_cookie("session" ) );
}

void Request_handler::fill_GET_exit()
{
    to_put_in_loop.emplace( "method", "GET" );
//    to_put_in_loop.emplace( "path", path );
    path.erase( 0, path.find('/') + 1 );
    to_put_in_loop.emplace( "roomID", room ); // из-за ? в конце пути
    to_put_in_loop.emplace( "path", "exit" );
    to_put_in_loop.emplace( "session", get_cookie("session" ) );
}

void Request_handler::fill_GET_logout()
{
    to_put_in_loop.emplace( "method", "GET" );
    to_put_in_loop.emplace( "path", path );
    to_put_in_loop.emplace( "session", get_cookie("session" ) );
}

void Request_handler::fill_GET_delete_room()
{
    to_put_in_loop.emplace( "method","GET" );
    to_put_in_loop.emplace( "path", "delete_room" );
    to_put_in_loop.emplace( "roomID", room );
    to_put_in_loop.emplace( "session", get_cookie("session" ) );
}

void Request_handler::fill_POST_login()
{
    to_put_in_loop.emplace( "method","POST" );
    to_put_in_loop.emplace( "path", path );
    to_put_in_loop.emplace( "login", get_data( "login" ) );
    to_put_in_loop.emplace( "password", get_data( "password" ) );
    to_put_in_loop.emplace( "session", get_cookie("session" ) );
}

void Request_handler::fill_POST_signup()
{
    to_put_in_loop.emplace( "method","POST" );
    to_put_in_loop.emplace( "path", path );
    to_put_in_loop.emplace( "login", get_data( "login" ) ) ;
    to_put_in_loop.emplace( "mail", get_data( "mail" ) ) ;
    to_put_in_loop.emplace( "password", get_data( "password" ) );
    to_put_in_loop.emplace( "session", get_cookie("session" ) );
}

void Request_handler::fill_POST_room()
{
    to_put_in_loop.emplace( "method","POST" );
//    to_put_in_loop.emplace( "path", path );
    to_put_in_loop.emplace( "path", "add" );
    to_put_in_loop.emplace( "room", room );
    to_put_in_loop.emplace( "session", get_cookie("session" ) );
    to_put_in_loop.emplace( "id_post", get_cookie("id_post" ) );
    to_put_in_loop.emplace("title", get_data( "title" ) );
    to_put_in_loop.emplace( "tag", get_data(  "tag" ) );
    to_put_in_loop.emplace( "text", get_data( "text" ) ); // text и fileurl не обязательно будут
    to_put_in_loop.emplace( "fileurl", get_data( "fileurl" ) );
}

void Request_handler::fill_POST_create_room()
{
    to_put_in_loop.emplace( "method","POST" );
    to_put_in_loop.emplace( "path", "create" );
    to_put_in_loop.emplace( "title", get_data( "title" ) );
    to_put_in_loop.emplace( "session", get_cookie("session" ) );
}

void Request_handler::fill_POST_join_room()
{
    to_put_in_loop.emplace( "method","POST" );
    to_put_in_loop.emplace( "path", "join" );
    to_put_in_loop.emplace( "roomID", get_data( "roomID" ) );
    to_put_in_loop.emplace( "session", get_cookie("session" ) );
}
