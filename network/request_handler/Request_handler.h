#ifndef PROFORGIA_REQUEST_HANDLER_H
#define PROFORGIA_REQUEST_HANDLER_H

#include <string>
#include <unordered_map>

using std::string;

class Request_handler
{
public:
    explicit Request_handler(const string &request );
    std::unordered_map<std::string, std::string> get_map() const;
private:
    std::unordered_map<std::string, std::string> to_put_in_loop;
    void create_map();
    void fill_GET_login();
    void fill_GET_signup();
    void fill_GET_profile();
    void fill_GET_room();
    void fill_POST_login();
    void fill_POST_signup();
    void fill_POST_room();

    std::unordered_map<std::string, std::string> data;
    std::unordered_map<std::string, std::string> cookies;
    string method;
    string path;
    string room;
    string tag;

    string get_data( const string &type );
    string get_cookie( const string &type );
};


#endif //PROFORGIA_REQUEST_HANDLER_H
