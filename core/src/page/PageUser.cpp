//
// Created by sergei on 28.11.2020.
//

#include "PageUser.h"

template<class View>
string PageUser<View>::get_main_page() {
    Context context = {{"page", "MAIN"}};
    return PageManager<View>::view_.render(context);
}

template<class View>
string PageUser<View>::get_room_page(string id) {
    return get_main_page();
}

template<class View>
string PageUser<View>::get_favorite_page() {
    return get_main_page();
}

template<class View>
string PageUser<View>::get_deadline_page() {
    return get_main_page();
}

template<class View>
string PageUser<View>::get_registr_page() {
    Context context = {{"page", "SIGNUP"}};
    return PageManager<View>::view_.render(context);
}

template<class View>
string PageUser<View>::get_login_page() {
    Context context = {{"page", "LOGIN"}};
    return PageManager<View>::view_.render(context);
}

template<class View>
string PageUser<View>::get_info_tags(int id_room, std::unique_ptr<std::vector<string>> tags) {
    return get_main_page();
}

template<class View>
string PageUser<View>::get_not_found() {
    Context context = {{"page", "NOT_FOUND"}};
    return PageManager<View>::view_.render(context);
}

template<class View>
string PageUser<View>::get_server_err() {
    Context context = {{"page", "500"}};
    return PageManager<View>::view_.render(context);
}
