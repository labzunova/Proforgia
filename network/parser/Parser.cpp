#include "Parser.h"


const string Parser::parse_method()
{
    string method;
    method = request.substr( 0, request.find(' ')); // первое слово до пробела в запросе - метод
    return method;
}

const string Parser::parse_path()
{
    string  temp = request,
            path;
    temp = temp.erase(0, request.find(' ') + 1); // удаляем метод и пробел между методом и путем
    path = temp.substr( 0, temp.find(' ')); // теперь часть до пробела - путь
    if ( path.at(0) == '/')
        path = path.erase( 0, 1 );
    return path;
}

const string Parser::parse_room_properties(string& path )
{
    return path.erase(0, path.find('/') + 1);
}

const unordered_map<string, string> Parser::parse_cookies()
{
    string request_ = request;
    unordered_map<string, string> cookie_values;
    string cookies = request_.erase( 0, request_.find( "\r\nCookie:" ) + 10 );
    cookies = cookies.erase( cookies.find("\r\n") );
    string key, value;
    while ( cookies.length() != 0 )
    {
        int index = cookies.find( '=' );
        key = cookies.substr( 0, index );
        int endpos = cookies.find( ';' );
        if( endpos == -1 ) endpos = cookies.length(); // если последняя кука
        value = cookies.substr( index + 1, endpos - index - 1 );
        cookie_values.insert(std::make_pair( key, value ));
        cookies.erase( 0, endpos + 2 );
    }
    return cookie_values;
}

const unordered_map<string, string> Parser::parse_body()
{
    string request_ = request;
    unordered_map<string, string> data;
    string body = request_.erase( 0, request_.find( "\r\n\r\n" ) + 4 ); // стираем все что до body
    string key, value;
    while ( body.length() != 0 )
    {
        int index = body.find( '=' );
        key = body.substr( 0, index );
        int endpos = body.find( '&' );
        if( endpos == -1 ) endpos = body.length(); // если последний параметр
        value = body.substr( index + 1, endpos - index - 1 );
        data.insert(std::make_pair( key, value ));
        body.erase( 0, endpos + 1 );
    }
    return data;
}





