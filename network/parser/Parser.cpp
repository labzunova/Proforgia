#include "Parser.h"


const string Parser::parse_method()
{
    string method;
    method = request.substr( 0, request.find(' ')); // первое слово до пробела в запросе - метод
    return method;
}

const string Parser::parse_path() { // !Учитывая то, что у нас в проекте не должно быть запросов с несколькими слэшами
    string temp,
            path;
    temp = request.erase(0, request.find(' ') + 1); // удаляем метод и пробел между методом и путем
    path = temp.substr( 0, temp.find(' ')); // теперь часть до пробела - путь
    if ( path.at(0) == '/')
        path = path.erase( 0, 1 );
    return path;
}

const unordered_map<string, string> Parser::parse_cookies()
{

}

const unordered_map<string, string> Parser::parse_data()
{

}



