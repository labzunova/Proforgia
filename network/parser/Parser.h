#ifndef PROFORGIA_PARSER_H
#define PROFORGIA_PARSER_H

#include <string>
#include <unordered_map>

using std::unordered_map;
using std::string;

class Parser // TODO: smth else to parse
{
public:
    Parser( string request_ );
    unordered_map<string, string> parse_cookies();
    unordered_map<string, string> parse_data();
    string parse_method();
private:
    string request;
};

#endif //PROFORGIA_PARSER_H
