//
// Created by sergei on 28.11.2020.
//

#include "PageUser.h"

template<class View>
string PageUser<View>::get_main_page() const {
    Context context = {{"page", "MAIN"}};
    return PageManager<View>::view_.render(context);
}

template<class View>
string PageUser<View>::get_room_page(int id) const {
    return get_main_page();
}

template<class View>
string PageUser<View>::get_favorite_page() const {
    return get_main_page();
}

template<class View>
string PageUser<View>::get_deadline_page() const {
    return get_main_page();
}

template<class View>
string PageUser<View>::get_registr_page() const {
    Context context = {{"page", "SIGNUP"}};
    return PageManager<View>::view_.render(context);
}

template<class View>
string PageUser<View>::get_login_page() const {
    Context context = {{"page", "LOGIN"}};
    return PageManager<View>::view_.render(context);
}

template<class View>
string PageUser<View>::get_info_tags(int id_room, std::unique_ptr<std::vector<string>> tags) const {
    return get_main_page();
}

template<class View>
string PageUser<View>::get_not_found() const {
    Context context = {{"page", "NOT_FOUND"}};
    return PageManager<View>::view_.render(context);
}
