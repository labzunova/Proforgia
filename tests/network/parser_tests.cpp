#include "gtest/gtest.h"
#include <string>

#include "parser/Parser.cpp" // wtf... TODO

TEST(method_parse_tests, oneline_first)
{
    string request = "GET /tutorials HTTP/1.1";
    Parser parser( request );
    string method = parser.parse_method();
    ASSERT_EQ( "GET", method );
}

TEST(method_parse_tests, oneline_second)
{
    string request = "POST /cgi-bin/process.cgi HTTP/1.1";
    Parser parser( request );
    string method = parser.parse_method();
    ASSERT_EQ( "POST", method );
}

TEST(method_parse_tests, full_first)
{
    string request = "GET /hello.htm HTTP/1.1\n"
                     "\n"
                     "User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\n"
                     "\n"
                     "Host: www.example.com\n"
                     "\n"
                     "Accept-Language: ru-ru\n"
                     "\n"
                     "Accept-Encoding: gzip, deflate\n"
                     "\n"
                     "Connection: Keep-Alive";
    Parser parser( request );
    string method = parser.parse_method();
    ASSERT_EQ( "GET", method );
}

TEST(method_parse_tests, full_second)
{
    string request = "POST /cgi-bin/process.cgi HTTP/1.1\n"
                     "\n"
                     "User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\n"
                     "\n"
                     "Host: www.example.com\n"
                     "\n"
                     "Content-Type: application/x-www-form-urlencoded\n"
                     "\n"
                     "Content-Length: length\n"
                     "\n"
                     "Accept-Language: ru-ru\n"
                     "\n"
                     "Accept-Encoding: gzip, deflate\n"
                     "\n"
                     "Connection: Keep-Alive\n"
                     "\n"
                     " \n"
                     "\n"
                     "licenseID=string&content=string&/paramsXML=string";
    Parser parser( request );
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

TEST(path_parse_tests, full_first)
{
    string request = "GET /hello HTTP/1.1\n"
                     "\n"
                     "User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\n"
                     "\n"
                     "Host: www.example.com\n"
                     "\n"
                     "Accept-Language: ru-ru\n"
                     "\n"
                     "Accept-Encoding: gzip, deflate\n"
                     "\n"
                     "Connection: Keep-Alive";
    Parser parser( request );
    string path = parser.parse_path();
    ASSERT_EQ( "hello", path );
}


