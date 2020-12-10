#ifndef PROFORGIA_SIGNUPTEMPLATE_H
#define PROFORGIA_SIGNUPTEMPLATE_H

#include "NLTemplate.h"
#include "BaseTemplate.h"

class SignUpTemplate : public BaseTemplate {
public:
    SignUpTemplate();
    std::string& getHTML();
private:
    std::string signUpHTML;
};


#endif //PROFORGIA_SIGNUPTEMPLATE_H
