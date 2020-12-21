#ifndef PROFORGIA_SIGNUPTEMPLATE_H
#define PROFORGIA_SIGNUPTEMPLATE_H

#include "BaseTemplate.h"

#define SIGNUP_WAY "../wt_templates/templates/signup.html"

class SignUpTemplate : public BaseTemplate {
public:
    SignUpTemplate(Context& context);
    std::string& getHTML() override;
private:
    std::string signUpHTML;
};


#endif //PROFORGIA_SIGNUPTEMPLATE_H
