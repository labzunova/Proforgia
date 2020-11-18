#ifndef PROFORGIA_PARSER_H
#define PROFORGIA_PARSER_H

#include <string>

class Parser // TODO: smth else to parse
{
public:
    Parser(std::string request);
    std::string parse_cookies();
    std::string parse_user();
    std::string parse_purpose();
private:
    std::string request;
    std::string purpose; // what should we do after this Request
    std::string cookies; // or array?
    std::string user;
};

#endif //PROFORGIA_PARSER_H
