#ifndef PROFORGIA_REPLY_H
#define PROFORGIA_REPLY_H

#include<string>
#include<unordered_map>
using std::string;

class Reply
{
public:
    void set_header(string header);
    void set_body(string body_); // TODO: ???
    void set_cookie(string cookie, string type);
    void set_status(int status); // 200, 404 итд
private:
    string header;
    int status;
    string body; // или не string?
    std::unordered_map<string, string> cookies;
};


#endif //PROFORGIA_REPLY_H
