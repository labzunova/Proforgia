//
// Created by sergei on 02.12.2020.
//

#include "HttpResponse.h"
#include <boost/log/trivial.hpp>


std::string HttpResponse::get_response(ContextMap& context) {
    std::string response;
    BOOST_LOG_TRIVIAL(info) << ("code " + context["code"]);

    if(context["code"][0] == '2') {
        response = get_response_200(context);
    } else if(context["code"][0] == '3') {
        response = get_response_300(context);
    } else if(context["code"][0] == '4') {
        response = get_response_400(context);
    }

    return response;
}

std::string HttpResponse::get_response_200(ContextMap& context) {
    return "HTTP/1.1 " + context["code"] + " OK\n"
        + "< Date: "+ context["date"] +"\n"
        + "< Server: " + context["server"] + "\n"
        + "< Content-Type: text/html; charset=utf-8\n"
        + "< X-Frame-Options: DENY\n"
        + "< Content-Length: " + context["content-length"] + "\n"
        + "< Vary: Cookie\n"
        + "< X-Content-Type-Options: nosniff\n"
        + "< Referrer-Policy: same-origin\n\n\n"
        + context["body"];
}

std::string HttpResponse::get_response_300(ContextMap& context) {
    return "HTTP/1.1 " + context["code"] + " Found\n"
           + "< Date: "+ context["date"] +"\n"
           + "< Server: " + context["server"] + "\n"
           + "< Content-Type: text/html; charset=utf-8\n"
           + "< Location: " + context["location"] + "\n"
           + "< X-Frame-Options: DENY\n"
           + "< Content-Length: 0\n"
           + "< Vary: Cookie\n"
           + "< X-Content-Type-Options: nosniff\n"
           + "< Referrer-Policy: same-origin";
}

std::string HttpResponse::get_response_400(ContextMap& context) {
    return "HTTP/1.1 " + context["code"] + " Not Found\n"
           + "< Date: "+ context["date"] +"\n"
           + "< Server: " + context["server"] + "\n"
           + "< Content-Type: text/html\n"
           + "< X-Frame-Options: DENY\n"
           + "< Content-Length: " + context["content-length"] + "\n"
           + "< X-Content-Type-Options: nosniff\n"
           + "< Referrer-Policy: same-origin\n\n\n"
           + context["body"];
}
