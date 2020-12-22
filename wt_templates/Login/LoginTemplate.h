#ifndef PROFORGIA_LOGINTEMPLATE_H
#define PROFORGIA_LOGINTEMPLATE_H

#include "NLTemplate.h"
#include "BaseTemplate.h"

#define LOGIN_WAY "../wt_templates/templates/login.html"

class LoginTemplate : public BaseTemplate {
public:
    LoginTemplate(Context& context);
    std::string& getHTML() override;
private:
    std::string loginHTML;
};


#endif //PROFORGIA_LOGINTEMPLATE_H
