#ifndef PROFORGIA_BASETEMPLATE_H
#define PROFORGIA_BASETEMPLATE_H

#include <vector>
#include <string>

class BaseTemplate {
public:
    BaseTemplate();
    virtual std::string& getHTML() = 0;

protected:
    std::vector<std::string> getCSS();

    std::vector<std::string> getJS();
};


#endif //PROFORGIA_BASETEMPLATE_H
