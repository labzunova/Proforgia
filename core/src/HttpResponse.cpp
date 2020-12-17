//
// Created by sergei on 02.12.2020.
//

#include "HttpResponse.h"
#include <boost/log/trivial.hpp>


string HttpResponse::get_response(ContextMap& context) {

    string response = "HTTP/1.1 " + context["Code"] + "\n";

    for(auto & item : context)
        if(item.first != "Body")
            response += item.first + ": " + item.second + "\n";

    response += "\n\n\n";

    if(context.find("Body") != context.end())
        response += context["Body"];

    return response;
}
