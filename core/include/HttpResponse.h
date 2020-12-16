//
// Created by sergei on 02.12.2020.
//

#pragma once
#include <string>
#include <map>

typedef std::map<std::string, std::string> ContextMap;
class HttpResponse {
public:
    static std::string get_response(ContextMap& context);

private:
    static std::string get_response_200(ContextMap& context);
    static std::string get_response_300(ContextMap& context);
    static std::string get_response_400(ContextMap& context);
};
