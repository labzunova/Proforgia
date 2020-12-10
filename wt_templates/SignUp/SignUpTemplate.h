#ifndef PROFORGIA_SIGNUPTEMPLATE_H
#define PROFORGIA_SIGNUPTEMPLATE_H

#include "NLTemplate.h"
#include "BaseTemplate.h"

class SignUpTemplate : BaseTemplate {
public:
    SignUpTemplate();
    std::string& getSignUpHTML();
private:
    std::string signUpHTML;
};


#endif //PROFORGIA_SIGNUPTEMPLATE_H
