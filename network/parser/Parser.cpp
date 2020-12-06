#include "Parser.h"

const unordered_map<string, string> Parser::parse_cookies()
{

}

const unordered_map<string, string> Parser::parse_data()
{

}

const string Parser::parse_method()
{
    string method;
    // basic_string& insert( size_type index, const CharT* s, size_type count );
    // Вставляет первые count символов из строки, на которую указывает s, в позицию index. Строка s может содержать нулевые символы.
    method.insert( 0, request, request.find(' ')); // первое слово до пробела в запросе - метод
    return method;
}

const string Parser::parse_path() {

}



