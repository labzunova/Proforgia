#include "Parser.h"
#include <curl/curl.h>


string Parser::parse_method() const
{
    return request.substr( 0, request.find(' '));// первое слово до пробела в запросе - метод
}

string Parser::parse_path() const
{
    string  temp = request,
            path;
    temp = temp.erase(0, request.find(' ') + 1); // удаляем метод и пробел между методом и путем
    path = temp.substr( 0, temp.find(' ')); // теперь часть до пробела - путь
    if ( path.at(0) == '/')
        path = path.erase( 0, 1 );
    return path;
}

std::pair<string, string> Parser::parse_room_properties( string& path ) const
{
    string room,
           tag;
    path.erase(0, path.find('/') + 1);
    if ( path.find( '/') != -1 ) // если требуется получить не просто комнату, а комнату с постами по тегу
    {
        room = path.substr( 0, path.find( '/' ) );
        tag = path.erase( 0, path.find( '/' ) + 1 );
    }
    else // если получить нужно просто конкретную комнату
        room = path;
    std::pair<string, string> properties = { room, tag };
    return properties;
}

unordered_map<string, string> Parser::parse_cookies() const
{
    unordered_map<string, string> cookie_values;
    if ( request.find( "\r\nCookie:" ) != -1)
    {
        string request_ = request;
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
    }
    return cookie_values;
}

unordered_map<string, string> Parser::parse_body() const
{
    string request_ = request;
    unordered_map<string, string> data;
    string body = request_.erase( 0, request_.find( "\r\n\r\n" ) + 4 ); // стираем все что до body
    body = body.substr( 0 , body.find( '\000' ) );
    string key, value;
    while ( body.length() != 0 )
    {
        int index = body.find( '=' );
        key = body.substr( 0, index );
        int endpos = body.find( '&' );
        if( endpos == -1 ) endpos = body.length(); // если последний параметр
        value = body.substr( index + 1, endpos - index - 1 );
        value = decode( value );
        value = replace_pluses( value );
        data.insert(std::make_pair( key, value ));
        body.erase( 0, endpos + 1 );
    }
    return data;
}

string Parser::parse_room_to_delete( string& path ) const
{
    path.erase(0, path.find('/') + 1);
    return path;
}

string Parser::decode( const string& sentence ) const
{
    CURL *curl = curl_easy_init();
    int outlength;
    char *cres = curl_easy_unescape( curl, sentence.c_str(), sentence.length(), &outlength );
    string res(cres, cres + outlength);
    curl_free(cres);
    curl_easy_cleanup(curl);
    return res;
}

string Parser::replace_pluses( string sentence ) const
{
    for( auto i = sentence.begin(); i < sentence.end(); i++ )
    {
        if ( *i == '+' )
            *i = ' ';
    }
    return sentence;
}
