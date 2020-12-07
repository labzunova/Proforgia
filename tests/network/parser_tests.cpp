#include "gtest/gtest.h"
#include <string>

#include "parser/Parser.cpp" // wtf...but working TODO

const static string POST_request1 = "POST /cgi-bin/process.cgi HTTP/1.1\r\n"
                                   "User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\r\n"
                                   "Host: www.example.com\r\n"
                                   "Content-Type: application/x-www-form-urlencoded\r\n"
                                   "Content-Length: length\r\n"
                                   "Accept-Language: ru-ru\r\n"
                                   "Accept-Encoding: gzip, deflate\r\n"
                                   "Connection: Keep-Alive\r\n"
                                   "Cookie: session=12345\r\n\r\n"
                                   "hello=world&content=string&key=12345";

const static string GET_request1 = "GET /hello/world HTTP/1.1\r\n"
                                  "User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\r\n"
                                  "Host: www.example.com\r\n"
                                  "Accept-Language: ru-ru\r\n"
                                  "Accept-Encoding: gzip, deflate\r\n"
                                  "Connection: Keep-Alive";

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
    Parser parser( GET_request1 );
    string method = parser.parse_method();
    ASSERT_EQ( "GET", method );
}

TEST( method_parse_tests, full_second )
{
    Parser parser( POST_request1 );
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
    Parser parser( GET_request1 );
    string path = parser.parse_path();
    ASSERT_EQ( "hello/world", path );
}

TEST( room_from_path_parse_tests, first )
{
    Parser parser( GET_request1 );
    string path = parser.parse_path();
    string room = parser.parse_room_from_path( path );
    ASSERT_EQ( "world", room );
}

TEST( body_parse_tests, first )
{
    Parser parser( POST_request1 );
    unordered_map<string, string> data = parser.parse_body();
    ASSERT_EQ( "world", data["hello"] );
    ASSERT_EQ( "12345", data["key"] );
    ASSERT_EQ( "string", data["content"] );
}

TEST( cookies_parse_tests, first )
{
    Parser parser( POST_request1 );
    unordered_map<string, string> cookies = parser.parse_cookies();
    ASSERT_EQ( "12345", cookies["session"] );
}



