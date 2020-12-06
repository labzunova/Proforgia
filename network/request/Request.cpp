#include "Request.h"
#include "parser/Parser.h"

Request::Request( const string &request )
{
    Parser parser( request );
    method = parser.parse_method();
    path = parser.parse_path();
    data = parser.parse_data();
    cookies = parser.parse_cookies();
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

const string Request::get_action()
{
    return path;
}
