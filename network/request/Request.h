#ifndef PROFORGIA_REQUEST_H
#define PROFORGIA_REQUEST_H

#include <string>
#include <unordered_map>

using std::string;

class Request
{
public:
    explicit Request( const string &request );
    const string get_data( string &type );
    const string get_cookie( string &type );
    const string get_path();
    const string get_method();
    const string get_room();
private:
    std::unordered_map<std::string, std::string> data;
    std::unordered_map<std::string, std::string> cookies;
    string method;
    string path;
    string room;
};


#endif //PROFORGIA_REQUEST_H
