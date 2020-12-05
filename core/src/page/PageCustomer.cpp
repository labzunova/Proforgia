//
// Created by sergei on 28.11.2020.
//

#include "PageCustomer.h"

#include <utility>

template<class View, class User, class Room>
PageCustomer<View, User, Room>::PageCustomer(const View &view, const User& user)
        : PageManager<View>(view)
        , user_(std::move(user)) {}



template<class View, class User, class Room>
string PageCustomer<View, User, Room>::get_main_page() const {
    Context context = {{"page", "MAIN"}};
    write_user(context); // TODO возможно сразу запись комнаты
    return PageManager<View>::view_.render(context);
}

template<class View, class User, class Room>
string PageCustomer<View, User, Room>::get_room_page(int id) const {
    Context context = {{"page", "ROOM"}};
    write_user(context);

    write_room(context, Room::get(id));
    return PageManager<View>::view_.render(context);
}

// TODO пока не известно будет ли это в проекте
template<class View, class User, class Room>
string PageCustomer<View, User, Room>::get_favorite_page() const {
    return get_main_page();
}

// TODO пока не известно будет ли это в проекте
template<class View, class User, class Room>
string PageCustomer<View, User, Room>::get_deadline_page() const {
    return get_main_page();
}

template<class View, class User, class Room>
string PageCustomer<View, User, Room>::get_registr_page() const {
    return get_main_page();
}

template<class View, class User, class Room>
string PageCustomer<View, User, Room>::get_login_page() const {
    return get_main_page();
}

template<class View, class User, class Room>
string PageCustomer<View, User, Room>::get_info_tags(int id_room, std::unique_ptr<std::vector<string>> tags) const {
    return std::__cxx11::string();
}

template<class View, class User, class Room>
string PageCustomer<View, User, Room>::get_not_found() const {
    Context context = {{"page", "NOT_FOUND"}};
    return PageManager<View>::view_.render(context);
}

template<class View, class User, class Room>
void PageCustomer<View, User, Room>::write_user(std::map<string, string> &ctx) {
    ctx["user_name"] = user_.nick_name;
    /// Добавление всей информации пользователя
}

template<class View, class User, class Room>
void PageCustomer<View, User, Room>::write_room(std::map<string, string> &ctx, const Room &room) {
    ctx["room_name"] = room.room_name;
    /// Добавление всей информации комнаты
}

template<class View, class User, class Room>
void PageCustomer<View, User, Room>::write_info_tag(std::map<string, string> &ctx, const Room &room, string tag) {

}
