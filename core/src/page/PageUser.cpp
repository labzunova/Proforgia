//
// Created by sergei on 28.11.2020.
//

#include "PageUser.h"

// TODO разобраться с ContextMap

string PageUser::get_main_page() {

    // хз как будет в итоговом проекте
    get_login_page();

    //
    string page = "main";
    Context context(page);
    TemplateWrapper view(context);
    return view.getHTML();
}

string PageUser::get_room_page(string id) {
    return get_main_page();
}

string PageUser::get_favorite_page() {
    return get_main_page();
}

string PageUser::get_deadline_page() {
    return get_main_page();
}

string PageUser::get_registr_page() {
    string page = "signup";
    Context context(page);
    TemplateWrapper view(context);
    return view.getHTML();
}

string PageUser::get_login_page() {
    string page = "login";
    Context context(page);
    TemplateWrapper view(context);
    return view.getHTML();
}

string PageUser::get_info_tags(int id_room, std::unique_ptr<std::vector<string>> tags) {
    return get_main_page();
}

string PageUser::get_not_found() {
    string page = "not_found";
    Context context(page);
    TemplateWrapper view(context);
    return view.getHTML();
}

string PageUser::get_server_err() {
    string page = "500";
    Context context(page);
    TemplateWrapper view(context);
    return view.getHTML();
}
