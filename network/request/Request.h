#ifndef PROFORGIA_REQUEST_H
#define PROFORGIA_REQUEST_H


#include <string>
#include <unordered_map>

using std::string;

class Request
{
public:
    explicit Request( const string &request );
    string get_data( string type );
    string get_cookie( string type );
    string get_method(); // GET or POST

private:
    std::unordered_map<std::string, std::string> data;
    std::unordered_map<std::string, std::string> cookies;
    string method;
};


#endif //PROFORGIA_REQUEST_H
