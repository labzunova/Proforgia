#ifndef PROFORGIA_BASETEMPLATE_H
#define PROFORGIA_BASETEMPLATE_H

#include <map>
#include <vector>
#include <string>

typedef std::map<std::string, std::string> Context;

class BaseTemplate {
public:
    BaseTemplate(Context& context);
    virtual std::string& getHTML() = 0;

protected:
    std::vector<std::string> getCSS();

    std::vector<std::string> getJS();

    Context& context;
};


#endif //PROFORGIA_BASETEMPLATE_H
