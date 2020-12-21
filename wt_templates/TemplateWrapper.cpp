#include "TemplateWrapper.h"

TemplateWrapper::TemplateWrapper(Context& context) {
    auto page = context.page;
    if (page == SIGNUP_PAGE) {
        temp = std::make_unique<SignUpTemplate>(context);
    } else if (page == LOGIN_PAGE) {
        temp = std::make_unique<LoginTemplate>(context);
    } else if (page == PROFILE_PAGE) {
        temp = std::make_unique<ProfileTemplate>(context);
    } else if (page == MAIN_PAGE || page == TAG_PAGE) {
        temp = std::make_unique<MainTemplate>(context);
    } else if (page == ADD_PAGE) {
        temp = std::make_unique<AddPostTemplate>(context);
    } else {
        temp = std::make_unique<NotFoundTemplate>(context);
    }
}

std::string& TemplateWrapper::getHTML() {
    return temp->getHTML();
}

