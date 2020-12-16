#ifndef PROFORGIA_SIGNUPTEMPLATE_H
#define PROFORGIA_SIGNUPTEMPLATE_H

#include "NLTemplate.h"
#include "BaseTemplate.h"

class SignUpTemplate : public BaseTemplate {
public:
    SignUpTemplate(ContextMap& context);
    std::string& getHTML() override;
private:
    std::string signUpHTML;
};


#endif //PROFORGIA_SIGNUPTEMPLATE_H
