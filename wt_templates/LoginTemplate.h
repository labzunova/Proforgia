#ifndef PROFORGIA_LOGINTEMPLATE_H
#define PROFORGIA_LOGINTEMPLATE_H

#include <Wt/WTemplate.h>
#include <Wt/WString.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>

class LoginTemplate : Wt::WTemplate {
public:
    LoginTemplate();
    Wt::WString getTemplateText();
};


#endif //PROFORGIA_LOGINTEMPLATE_H
