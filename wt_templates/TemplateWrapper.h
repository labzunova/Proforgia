#ifndef PROFORGIA_TEMPLATEWRAPPER_H
#define PROFORGIA_TEMPLATEWRAPPER_H

#include <map>
#include <memory>

#include "Login/LoginTemplate.h"
#include "SignUp/SignUpTemplate.h"

typedef std::map<std::string, std::string> Context;

class TemplateWrapper {
public:
    explicit TemplateWrapper(Context& context);
    std::string& getHTML();

private:
    std::unique_ptr<BaseTemplate> temp;
};


#endif //PROFORGIA_TEMPLATEWRAPPER_H
