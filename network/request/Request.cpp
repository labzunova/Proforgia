#include "Request.h"
#include "parser/Parser.h"

Request::Request( const string &request )
{
// создается объект класса Parser и вызываются
// методы парсинга разных частей запроса
}

const string Request::get_data( string type )
{
    return data[type];
}

const string Request::get_cookie( string type )
{
    return cookies[type];
}

const string Request::get_method()
{
    return method;
}

const string Request::get_action() {
    return action;
}
