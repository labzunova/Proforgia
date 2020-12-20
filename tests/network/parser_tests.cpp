#include "gtest/gtest.h"
#include <string>

#include "src/Parser.cpp" // wtf...but working TODO

const static string POST_request_random1 = "POST /login/process.cgi HTTP/1.1\r\n"
                                           "User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\r\n"
                                           "Host: www.example.com\r\n"
                                           "Cont"
                                           "ent-Type: application/x-www-form-urlencoded\r\n"
                                           "Content-Length: length\r\n"
                                           "Accept-Language: ru-ru\r\n"
                                           "Accept-Encoding: gzip, deflate\r\n"
                                           "Connection: Keep-Alive\r\n"
                                           "Cookie: session=12345\r\n\r\n"
                                           "hello=world&content=string&key=12345";

const static string POST_request_random2 = "POST /cgi-bin/process.cgi HTTP/1.1\r\n"
                                           "User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\r\n"
                                           "Host: www.example.com\r\n"
                                           "Content-Type: application/x-www-form-urlencoded\r\n"
                                           "Content-Length: length\r\n"
                                           "Accept-Language: ru-ru\r\n"
                                           "Accept-Encoding: gzip, deflate\r\n"
                                           "Connection: Keep-Alive\r\n"
                                           "Cookie: PHPSESSID=298zf09hf012fh2; csrftoken=u32t4o3tb3gg43; _gat=1\r\n\r\n"
                                           "hello=world&content=string&key=12345";

const static string POST_request_login = "POST /login HTTP/1.1\r\n"
                                         "User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\r\n"
                                         "Host: www.example.com\r\n"
                                         "Content-Type: application/x-www-form-urlencoded\r\n"
                                         "Content-Length: length\r\n"
                                         "Accept-Language: ru-ru\r\n"
                                         "Accept-Encoding: gzip, deflate\r\n"
                                         "Connection: Keep-Alive\r\n\r\n"
                                         "login=name&password=12345";

const static string POST_request_signup = "POST /signup HTTP/1.1\r\n"
                                          "User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\r\n"
                                          "Host: www.example.com\r\n"
                                          "Content-Type: application/x-www-form-urlencoded\r\n"
                                          "Content-Length: length\r\n"
                                          "Accept-Language: ru-ru\r\n"
                                          "Accept-Encoding: gzip, deflate\r\n"
                                          "Connection: Keep-Alive\r\n\r\n"
                                          "login=name&mail=name@gmail.com&password=12345";

const static string POST_request_addpost = "POST /room/room1 HTTP/1.1\r\n"
                                           "User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\r\n"
                                           "Host: www.example.com\r\n"
                                           "Content-Type: application/x-www-form-urlencoded\r\n"
                                           "Content-Length: length\r\n"
                                           "Accept-Language: ru-ru\r\n"
                                           "Accept-Encoding: gzip, deflate\r\n"
                                           "Connection: Keep-Alive\r\n"
                                           "Cookie: session=dfsd54h4telngdfjgod5\r\n\r\n"
                                           "title=first&text=hello!&fileurl=s3url&tag=math";

const static string POST_create_room = "POST /create HTTP/1.1\r\n"
                                       "User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\r\n"
                                       "Host: www.example.com\r\n"
                                       "Content-Type: application/x-www-form-urlencoded\r\n"
                                       "Content-Length: length\r\n"
                                       "Accept-Language: ru-ru\r\n"
                                       "Accept-Encoding: gzip, deflate\r\n"
                                       "Connection: Keep-Alive\r\n"
                                       "Cookie: session=dfsd54h4telngdfjgod5\r\n\r\n"
                                       "title=newroomtojoin";

const static string GET_request_room = "GET /room/room1 HTTP/1.1\r\n"
                                   "User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\r\n"
                                   "Host: www.example.com\r\n"
                                   "Accept-Language: ru-ru\r\n"
                                   "Accept-Encoding: gzip, deflate\r\n"
                                   "Connection: Keep-Alive\r\n"
                                   "Cookie: session=12345\r\n\r\n";

const static string GET_request_delete_room = "GET /delete_room/room1 HTTP/1.1\r\n"
                                       "User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\r\n"
                                       "Host: www.example.com\r\n"
                                       "Accept-Language: ru-ru\r\n"
                                       "Accept-Encoding: gzip, deflate\r\n"
                                       "Connection: Keep-Alive\r\n"
                                       "Cookie: session=12345\r\n\r\n";

const static string GET_request2 = "GET /room/room1/math HTTP/1.1\r\n"
                                   "User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\r\n"
                                   "Host: www.example.com\r\n"
                                   "Accept-Language: ru-ru\r\n"
                                   "Accept-Encoding: gzip, deflate\r\n"
                                   "Connection: Keep-Alive\r\n"
                                   "Cookie: session=sessionforroom\r\n\r\n";

TEST( method_parse_tests, oneline_first )
{
    string request = "GET /tutorials HTTP/1.1";
    Parser parser( request );
    string method = parser.parse_method();
    ASSERT_EQ( "GET", method );
}

TEST( method_parse_tests, oneline_second )
{
    string request = "POST /cgi-bin/process.cgi HTTP/1.1";
    Parser parser( request );
    string method = parser.parse_method();
    ASSERT_EQ( "POST", method );
}

TEST( method_parse_tests, full_first )
{
    Parser parser(GET_request_room );
    string method = parser.parse_method();
    ASSERT_EQ( "GET", method );
}

TEST( method_parse_tests, full_second )
{
    Parser parser( POST_request_random1 );
    string method = parser.parse_method();
    ASSERT_EQ( "POST", method );
}

TEST(path_parse_tests, oneline_first)
{
    string request = "GET /tutorials HTTP/1.1";
    Parser parser( request );
    string path = parser.parse_path();
    ASSERT_EQ( "tutorials", path );
}

TEST( path_parse_tests, full_first )
{
    Parser parser(GET_request_room );
    string path = parser.parse_path();
    ASSERT_EQ( "rooms/room1", path );
}

TEST( room_from_path_parse_tests, first )
{
    Parser parser(GET_request_room );
    string path = parser.parse_path();
    std::pair<string, string> room = parser.parse_room_properties(path);
    ASSERT_EQ( "room1", room.first );
    ASSERT_EQ( "", room.second );
}

TEST( body_parse_tests, first )
{
    Parser parser( POST_request_random1 );
    unordered_map<string, string> data = parser.parse_body();
    ASSERT_EQ( "world", data["hello"] );
    ASSERT_EQ( "12345", data["key"] );
    ASSERT_EQ( "string", data["content"] );
}

TEST( cookies_parse_tests, first )
{
    Parser parser( POST_request_random1 );
    unordered_map<string, string> cookies = parser.parse_cookies();
    ASSERT_EQ( "12345", cookies["session"] );
}

TEST( cookies_parse_tests, second )
{
    Parser parser(POST_request_random2 );
    unordered_map<string, string> cookies = parser.parse_cookies();
    ASSERT_EQ( "298zf09hf012fh2", cookies["PHPSESSID"] );
    ASSERT_EQ( "u32t4o3tb3gg43", cookies["csrftoken"] );
    ASSERT_EQ( "1", cookies["_gat"] );
}

/// Далее проверка запросов, которые реально должны быть в проекте(с погрешностью разных необязательных заголовков)

TEST( full_parse_tests, GET_room ) // запрос на получение конкретной комнаты
{
    Parser parser( GET_request_room );
    string method = parser.parse_method();
    ASSERT_EQ( method, "GET" );
    string path = parser.parse_path();
    ASSERT_EQ( "room/room1", path );
    std::pair<string, string> room = parser.parse_room_properties( path );
    ASSERT_EQ( "room1", room.first );
    ASSERT_EQ( "", room.second );
    unordered_map<string, string> cookies = parser.parse_cookies();
    ASSERT_EQ( "12345", cookies["session"] );
}

TEST( full_parse_tests, GET_room_tag ) // запрос на получение конкретной комнаты с постами по тегу
{
    Parser parser( GET_request2 );
    string method = parser.parse_method();
    ASSERT_EQ( method, "GET" );
    string path = parser.parse_path();
    ASSERT_EQ( "room/room1/math", path );
    std::pair<string, string> room = parser.parse_room_properties( path );
    ASSERT_EQ( "room1", room.first );
    ASSERT_EQ( "math", room.second );
    unordered_map<string, string> cookies = parser.parse_cookies();
    ASSERT_EQ( "sessionforroom", cookies["session"] );
}

TEST( full_parse_tests, GET_delete_room ) // запрос на получение конкретной комнаты
{
    Parser parser( GET_request_delete_room );
    string method = parser.parse_method();
    ASSERT_EQ( method, "GET" );
    string path = parser.parse_path();
    ASSERT_EQ( "delete_room/room1", path );
    string room = parser.parse_room_to_delete( path );
    ASSERT_EQ( "room1", room );
    unordered_map<string, string> cookies = parser.parse_cookies();
    ASSERT_EQ( "12345", cookies["session"] );
}


TEST( full_parse_tests, POST_login ) // запрос на то чтобы войти
{
    Parser parser( POST_request_login );
    string method = parser.parse_method();
    ASSERT_EQ( method, "POST" );
    string path = parser.parse_path();
    ASSERT_EQ( "login", path );
    unordered_map<string, string> data = parser.parse_body();
    ASSERT_EQ( "name", data["login"] );
    ASSERT_EQ( "12345", data["password"] );
}

TEST( full_parse_tests, POST_signup ) // запрос на то чтобы зарегистрироваться
{
    Parser parser( POST_request_signup );
    string method = parser.parse_method();
    ASSERT_EQ( method, "POST" );
    string path = parser.parse_path();
    ASSERT_EQ( "signup", path );
    unordered_map<string, string> data = parser.parse_body();
    ASSERT_EQ( "name", data["login"] );
    ASSERT_EQ( "name@gmail.com", data["mail"] );
    ASSERT_EQ( "12345", data["password"] );
}

TEST( full_parse_tests, POST_addpost ) // запрос на добавление поста(файла и/или текста с тегом)
{
    Parser parser( POST_request_addpost );
    string method = parser.parse_method();
    ASSERT_EQ( method, "POST" );
    string path = parser.parse_path();
    ASSERT_EQ( "room/room1", path );
    string room = parser.parse_room_properties( path ).first;
    ASSERT_EQ( "room1", room );
    unordered_map<string, string> data = parser.parse_body();
    ASSERT_EQ( "first", data["title"] );
    ASSERT_EQ( "hello!", data["text"] );
    ASSERT_EQ( "math", data["tag"] );
    ASSERT_EQ( "s3url", data["fileurl"] );
    unordered_map<string, string> cookies = parser.parse_cookies();
    ASSERT_EQ( "dfsd54h4telngdfjgod5", cookies["session"] );
}


TEST( full_parse_tests, POST_createroom ) // запрос на создание комнаты
{
    Parser parser( POST_create_room );
    string method = parser.parse_method();
    ASSERT_EQ( method, "POST" );
    string path = parser.parse_path();
    ASSERT_EQ( "create", path );
    unordered_map<string, string> data = parser.parse_body();
    ASSERT_EQ( "newroomtojoin", data["title"] );
    unordered_map<string, string> cookies = parser.parse_cookies();
    ASSERT_EQ( "dfsd54h4telngdfjgod5", cookies["session"] );
}
