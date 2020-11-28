#pragma once

//#include "Context.h"
#include <string>

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
    void SetPage(Page);
    std::string Render();
};
