//
// Created by sergei on 02.12.2020.
//

#include "HttpResponse.h"
#include "gtest/gtest.h"
#include <string>
#include <map>

typedef std::map<std::string, std::string> Context;

TEST(HttpResponseTests, HttpResponse_200){
    Context context{
            {"code", "200"},
            {"content-length", "16001"},
            {"date", "Wed, 02 Dec 2020 15:14:34 GMT"},
            {"server", "WSGIServer/0.2 CPython/3.6.9"},
            {"body", "<html>"},
    };

    std::string answer =
            "< HTTP/1.1 200 OK\n"
            "< Date: Wed, 02 Dec 2020 15:14:34 GMT\n"
            "< Server: WSGIServer/0.2 CPython/3.6.9\n"
            "< Content-Type: text/html; charset=utf-8\n"
            "< X-Frame-Options: DENY\n"
            "< Content-Length: 16001\n"
            "< Vary: Cookie\n"
            "< X-Content-Type-Options: nosniff\n"
            "< Referrer-Policy: same-origin\n\n\n"
            "<html>";

    EXPECT_EQ(answer, HttpResponse::get_response(context));
}

TEST(HttpResponseTests, HttpResponse_300){
    Context context{
            {"code", "302"},
            {"content-length", "0"},
            {"date", "Wed, 02 Dec 2020 15:40:22 GMT"},
            {"server", "WSGIServer/0.2 CPython/3.6.9"},
            {"location", "/"},
    };

    std::string answer =
            "< HTTP/1.1 302 Found\n"
            "< Date: Wed, 02 Dec 2020 15:40:22 GMT\n"
            "< Server: WSGIServer/0.2 CPython/3.6.9\n"
            "< Content-Type: text/html; charset=utf-8\n"
            "< Location: /\n"
            "< X-Frame-Options: DENY\n"
            "< Content-Length: 0\n"
            "< Vary: Cookie\n"
            "< Set-Cookie: lol=kek; Expires=Wed, 21 Oct 2015 07:28:00\n"
            "< GMT; Secure; HttpOnly; Domain: 127.0.0.1:3000"
            "< X-Content-Type-Options: nosniff\n"
            "< Referrer-Policy: same-origin";

    EXPECT_EQ(answer, HttpResponse::get_response(context));
}

TEST(HttpResponseTests, HttpResponse_400){
    Context context{
            {"code", "404"},
            {"content-length", "3062"},
            {"date", "Wed, 02 Dec 2020 15:45:27 GMT"},
            {"server", "WSGIServer/0.2 CPython/3.6.9"},
            {"body", "<html>"},
    };

    std::string answer =
            "< HTTP/1.1 404 Not Found\n"
            "< Date: Wed, 02 Dec 2020 15:45:27 GMT\n"
            "< Server: WSGIServer/0.2 CPython/3.6.9\n"
            "< Content-Type: text/html\n"
            "< X-Frame-Options: DENY\n"
            "< Content-Length: 3062\n"
            "< X-Content-Type-Options: nosniff\n"
            "< Referrer-Policy: same-origin\n\n\n"
            "<html>";

    EXPECT_EQ(answer, HttpResponse::get_response(context));
}
