#pragma once

#include <string>
#include <map>

typedef std::map<std::string, std::string> Context;

class TemplateWrapper {
public:
    TemplateWrapper() = default;

    enum Page {
        MAIN,
        LOGIN,
        ROOM,
        REG,
        FILE,
    };

public:
    std::string render(Context& context) {
        std::string response;

        response = "page: " + context["page"] + "\n";
        if(context.find("user_name") != context.end())
            response += "user_name: " + context["user_name"] + "\n";
        if(context.find("room_name") != context.end())
            response += "room_name: " + context["room_name"] + "\n";

        return response;
    }
};
