#include "Request.h"
#include "../parser/Parser.h"

Request::Request( const string &request )
{
// создается объект класса Parser и вызываются
// методы парсинга разных частей запроса
}

string Request::get_data( string type )
{
    return data[type];
}

string Request::get_cookie( string type )
{
    return cookies[type];
}

string Request::get_method()
{
    return method;
}
