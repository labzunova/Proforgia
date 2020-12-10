//
// Created by sergei on 28.11.2020.
//

#include "PageUser.h"

string PageUser::get_main_page() {
    Context context = {{"page", "main"}};
    return PageManager::view_.render(context);
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
    Context context = {{"page", "signup"}};
    return PageManager::view_.render(context);
}

string PageUser::get_login_page() {
    Context context = {{"page", "login"}};
    return PageManager::view_.render(context);
}

string PageUser::get_info_tags(int id_room, std::unique_ptr<std::vector<string>> tags) {
    return get_main_page();
}

string PageUser::get_not_found() {
    Context context = {{"page", "not_found"}};
    return PageManager::view_.render(context);
}

string PageUser::get_server_err() {
    Context context = {{"page", "500"}};
    return PageManager::view_.render(context);
}
