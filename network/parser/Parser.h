<<<<<<< HEAD
#ifndef PROFORGIA_PARSER_H
#define PROFORGIA_PARSER_H

#include <string>
#include <unordered_map>

using std::unordered_map;
using std::string;

class Parser // TODO: smth else to parse
{
public:
    Parser();
    static unordered_map<string, string> parse_cookies(string request);
    static unordered_map<string, string> parse_data(string request);
    static string parse_method(string request);
};

#endif //PROFORGIA_PARSER_H
=======
#ifndef PROFORGIA_PARSER_H
#define PROFORGIA_PARSER_H

#include <string>
#include <unordered_map>

using std::unordered_map;
using std::string;

class Parser // TODO: smth else to parse
{
public:
    Parser();
    static unordered_map<string, string> parse_cookies(string request);
    static unordered_map<string, string> parse_data(string request);
    static string parse_method(string request);
};

#endif //PROFORGIA_PARSER_H
>>>>>>> new casrass
