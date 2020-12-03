#ifndef PROFORGIA_REQUEST_H
#define PROFORGIA_REQUEST_H

#include <string>
#include <unordered_map>

using std::string;

class Request
{
public:
    explicit Request( const string &request );
    const string get_data( string type );
    const string get_cookie( string type );
    const string get_action();
    const string get_method(); // GET or POST
private:
    std::unordered_map<std::string, std::string> data;
    std::unordered_map<std::string, std::string> cookies;
    string method;
    string action;
};


#endif //PROFORGIA_REQUEST_H
