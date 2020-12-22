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
};
