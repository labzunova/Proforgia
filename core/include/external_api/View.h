#pragma once

#include <string>
#include <map>

typedef std::map<std::string, std::string> Context;

class View {
public:
    View() = default;

    enum Page {
        MAIN,
        LOGIN,
        ROOM,
        REG,
        FILE,
    };

public:
    std::string render(Context& context) {
        return "<html>";
    }
};
