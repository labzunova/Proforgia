#ifndef PROFORGIA_BASETEMPLATE_H
#define PROFORGIA_BASETEMPLATE_H

#include <map>
#include <vector>
#include <string>
#include "NLTemplate.h"
#include "../Context.h"

using namespace NL::Template;

class BaseTemplate {
public:
    BaseTemplate(Context& context);
    virtual std::string& getHTML() = 0;

protected:
    std::vector<std::string> getCSS();

    std::vector<std::string> getJS();

    void setLoggedNavBar(Template& temp) const;

    void setRightBlock(Template& temp);

    Context& context;
};


#endif //PROFORGIA_BASETEMPLATE_H
