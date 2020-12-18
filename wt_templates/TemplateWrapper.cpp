#include "TemplateWrapper.h"

TemplateWrapper::TemplateWrapper(Context& context) {
    auto page = context.page;
    if (page == "signup") {
        temp = std::make_unique<SignUpTemplate>(context);
    } else if (page == "login") {
        temp = std::make_unique<LoginTemplate>(context);
    } else if (page == "profile") {
        temp = std::make_unique<ProfileTemplate>(context);
    } else if (page == "main" || page == "tag") {
        temp = std::make_unique<MainTemplate>(context);
    } else if (page == "add") {
        temp = std::make_unique<AddPostTemplate>(context);
    } else {
        temp = std::make_unique<NotFoundTemplate>(context);
    }
}

std::string& TemplateWrapper::getHTML() {
    return temp->getHTML();
}

