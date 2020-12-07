#ifndef PROFORGIA_PARSER_H
#define PROFORGIA_PARSER_H

#include <string>
#include <unordered_map>
#include <utility>

// ПРИМЕРЫ

// POST /login.php HTTP/1.1
// Host: vkontakte.ru
// User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; ru; rv:1.9.0.3) Gecko/2008092417 AdCentriaIM/1.7 Firefox/3.0.3 WebMoney Advisor
// Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
// Accept-Language: ru,en-us;q=0.7,en;q=0.3
// Accept-Encoding: gzip,deflate
// Accept-Charset: windows-1251,utf-8;q=0.7,*;q=0.7
// Keep-Alive: 300
// Connection: keep-alive
//        Content-Type: application/x-www-form-urlencoded; charset=UTF-8
// Referer: http://vkontakte.ru/
// Content-Length: 69
// Cookie: remixchk=5; remixautobookmark=6; remixlang=0
// Pragma: no-cache
//         Cache-Control: no-cache
//         op=a_login_attempt&email=xxxxxx%40xxxxxx.ru&pass=xxxxxx&expire=0

// GET /2009/03/17/kak-zapretit-redaktirovanie-vyborochnyx-strok-v-cxgrid/ HTTP/1.1
// Host: www.blogok.ru
//        User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; ru; rv:1.9.0.8) Gecko/2009032609 Firefox/3.0.8
// Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
// Accept-Language: ru,en-us;q=0.7,en;q=0.3
// Accept-Encoding: gzip,deflate
// Accept-Charset: windows-1251,utf-8;q=0.7,*;q=0.7
// Keep-Alive: 300
// Connection: keep-alive
// Referer: http://www.blogok.ru/
// Cookie: PHPSESSID=562b6b2d17e9207d1551922da511c156

using std::unordered_map;
using std::string;

class Parser
{
public:
    Parser( string request_ ): request( std::move( request_ ) ) {};
    string request;
    const unordered_map<string, string> parse_cookies();
    const unordered_map<string, string> parse_body();
    const string parse_method();
    const string parse_path();
    const string parse_room_from_path( string path );
};

#endif //PROFORGIA_PARSER_H
