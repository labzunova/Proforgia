#ifndef PROFORGIA_LOGINTEMPLATE_H
#define PROFORGIA_LOGINTEMPLATE_H

#include "NLTemplate.h"
#include "BaseTemplate.h"

class LoginTemplate : BaseTemplate {
public:
    LoginTemplate();
    std::string& getLoginHTML();
private:
    std::string loginHTML;
};


#endif //PROFORGIA_LOGINTEMPLATE_H
