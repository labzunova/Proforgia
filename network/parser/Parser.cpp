#include "Parser.h"

 // вычленение информации из реквеста
Parser::Parser(std::string request) {

}

std::string Parser::parse_cookies() {
    return cookies;
}

std::string Parser::parse_user() {
    return user;
}

std::string Parser::parse_purpose() {
    return purpose;
}
