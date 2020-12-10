#ifndef PROFORGIA_BASETEMPLATE_H
#define PROFORGIA_BASETEMPLATE_H

#include <vector>
#include <string>

class BaseTemplate {
public:
    BaseTemplate();

protected:
    std::vector<std::string> getCSS();
    std::vector<std::string> getJS();
};


#endif //PROFORGIA_BASETEMPLATE_H
