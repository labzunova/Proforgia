#include "TemplateWrapper.h"

TemplateWrapper::TemplateWrapper(Context& context) {
    auto page = context.at("page");
    if (page == "login") {
        temp = std::make_unique<LoginTemplate>(context);
    } else if (page == "signup") {
        temp = std::make_unique<SignUpTemplate>(context);
    } else if (page == "profile") {
        temp = std::make_unique<ProfileTemplate>(context);
    } else if (page == "main") {
        temp = std::make_unique<LoginTemplate>(context);
    } else {
        temp = std::make_unique<LoginTemplate>(context);
    }
}

std::string& TemplateWrapper::getHTML() {
    return temp->getHTML();
}

