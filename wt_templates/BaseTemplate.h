#ifndef PROFORGIA_BASETEMPLATE_H
#define PROFORGIA_BASETEMPLATE_H

#include <map>
#include <vector>
#include <string>

//typedef std::map<std::string, std::string> ContextMap;

class BaseTemplate {
public:
    BaseTemplate(ContextMap& context);
    virtual std::string& getHTML() = 0;

protected:
    std::vector<std::string> getCSS();

    std::vector<std::string> getJS();

    ContextMap& context;
};


#endif //PROFORGIA_BASETEMPLATE_H
