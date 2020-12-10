#include "TemplateWrapper.h"

TemplateWrapper::TemplateWrapper(Context& context) {
    auto page = context.at("page");
    if (page == "login") {
        temp = std::make_unique<LoginTemplate>();
    } else if (page == "signup") {
        temp = std::make_unique<SignUpTemplate>();
    } else if (page == "profile") {
        temp = std::make_unique<LoginTemplate>();
    } else if (page == "main") {
        temp = std::make_unique<LoginTemplate>();
    } else {
        temp = std::make_unique<LoginTemplate>();
    }
}

std::string& TemplateWrapper::getHTML() {
    return temp->getHTML();
}

