//
// Created by sergei on 28.11.2020.
//

#include "PageUser.h"

PageManager::Status PageUser::get_signup_page(std::string& body) {
    std::string page = "signup";
    Context context(page);
    TemplateWrapper view(context);
    body = view.getHTML();
    return OK;
}

PageManager::Status PageUser::get_login_page(std::string& body) {
    std::string page = "login";
    Context context(page);
    TemplateWrapper view(context);
    body = view.getHTML();
    return OK;
}

PageManager::Status PageUser::get_not_found(std::string& body) {
    std::string page = "not_found";
    Context context(page);
    TemplateWrapper view(context);
    body = view.getHTML();
    return OK;
}

PageManager::Status PageUser::get_server_err(std::string& body) {
    std::string page = "500";
    Context context(page);
    TemplateWrapper view(context);
    body = view.getHTML();
    return OK;
}
