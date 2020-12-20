#ifndef PROFORGIA_TEMPLATEWRAPPER_H
#define PROFORGIA_TEMPLATEWRAPPER_H

#include <memory>

#include "Login/LoginTemplate.h"
#include "SignUp/SignUpTemplate.h"
#include "Profile/ProfileTemplate.h"
#include "Main/MainTemplate.h"
#include "AddPost/AddPostTemplate.h"
#include "NotFound/NotFoundTemplate.h"

class TemplateWrapper {
public:
    explicit TemplateWrapper(Context& context);
    std::string& getHTML();

private:
    std::unique_ptr<BaseTemplate> temp;
};


#endif //PROFORGIA_TEMPLATEWRAPPER_H
