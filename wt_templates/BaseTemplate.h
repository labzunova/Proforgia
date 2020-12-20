#ifndef PROFORGIA_BASETEMPLATE_H
#define PROFORGIA_BASETEMPLATE_H

#include <map>
#include <vector>
#include <string>
#include "NLTemplate.h"
#include "../Context.h"

#define LOGIN_PAGE "login"
#define SIGNUP_PAGE "signup"
#define PROFILE_PAGE "profile"
#define MAIN_PAGE "main"
#define TAG_PAGE "tag"
#define ADD_PAGE "add"

#define BASE_LOGGED_BLOCK "logged_block"
#define BASE_LOGGED_BLOCK_USERNAME "username"
#define BASE_LOGGED_BLOCK_AVATAR "avatar_res"

#define BASE_RIGHT_BLOCK "right_block.tags"
#define BASE_RIGHT_BLOCK_TAG_NAME "tag"
#define BASE_RIGHT_BLOCK_TAG_SRC "tag.url"

using namespace NL::Template;

class BaseTemplate {
public:
    explicit BaseTemplate(Context& context);
    virtual std::string& getHTML() = 0;

protected:
    std::vector<std::string> getCSS();

    std::vector<std::string> getJS();

    void setLoggedNavBar(Template& temp) const;

    static void offLoggedNavBar(Template& temp);

    void setRightBlock(Template& temp);

    Context& context;
};


#endif //PROFORGIA_BASETEMPLATE_H
