//
// Created by sergei on 02.12.2020.
//

#pragma once
#include <string>
#include <map>

typedef std::map<std::string, std::string> Context;
class HttpResponse {
public:
    static std::string get_response(Context& context);

private:
    static std::string get_response_200(Context& context);
    static std::string get_response_300(Context& context);
    static std::string get_response_400(Context& context);
};
