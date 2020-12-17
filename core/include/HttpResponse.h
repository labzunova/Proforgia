//
// Created by sergei on 02.12.2020.
//

#pragma once
#include <string>
#include <map>

using std::string;
typedef std::map<string, string> ContextMap;

class HttpResponse {
public:
    static string get_response(ContextMap& context);
};
