#include "Request.h"
#include "parser/Parser.h"

Request::Request( const string &request )
{
    Parser parser( request );
    method = parser.parse_method();
    path = parser.parse_path();
    cookies = parser.parse_cookies();
    if( method == "POST" )
        data = parser.parse_body();
    if( path.find( "rooms" ) != 0 ) // если это запрос на какую-то комнату: выяснить, какую
    {
        path = parser.parse_room_properties( path );
        if ( path.find( '/') != -1 ) // если требуется получить не просто комнату, а комнату с постами по тегу
        {
            room = path.substr( 0, room.find( '/' ) );
            tag = path.erase( 0, path.find( '/' ) + 1 );
        }
        else // если получить нужно просто конкретную комнату
            room = path;
    }
}

const string Request::get_data( string &type )
{
    return data[type];
}

const string Request::get_cookie( string &type )
{
    return cookies[type];
}

const string Request::get_method()
{
    return method;
}

const string Request::get_path()
{
    return path;
}

const string Request::get_room()
{
    return room;
}

const string Request::get_tag_for_room() {
    return tag;
}
