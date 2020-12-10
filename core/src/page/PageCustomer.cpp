//
// Created by sergei on 28.11.2020.
//

#include "PageCustomer.h"

#include <utility>
#include <boost/lexical_cast.hpp>

PageCustomer::PageCustomer(DBUser& user)
        : user_(std::move(user)) {}


string PageCustomer::get_main_page() {
    Context context = {{"page", "main"}};
    write_user(context); // TODO возможно сразу запись комнаты
    return PageManager::view_.render(context);
}

string PageCustomer::get_room_page(string id) {
    Context context = {{"page", "room"}};
    write_user(context);

    int id_room = boost::lexical_cast<int>(id);
    ErrorCodes er;
    write_room(context, *DBRoom::get(id_room, er));
    return PageManager::view_.render(context);
}

// TODO пока не известно будет ли это в проекте
string PageCustomer::get_favorite_page() {
    return get_main_page();
}

// TODO пока не известно будет ли это в проекте
string PageCustomer::get_deadline_page() {
    return get_main_page();
}

string PageCustomer::get_registr_page() {
    return get_main_page();
}

string PageCustomer::get_login_page() {
    return get_main_page();
}

string PageCustomer::get_info_tags(int id_room, std::unique_ptr<std::vector<string>> tags) {
    return "fdfdsgdsfgdsfgdfgdsfgsdfgdfglgiggglkdfsj";
}

string PageCustomer::get_not_found() {
    Context context = {{"page", "not_found"}};
    return PageManager::view_.render(context);
}

void PageCustomer::write_user(std::map<string, string> &ctx) {
    ctx["user_name"] = user_.nick_name;
    /// Добавление всей информации пользователя
}

void PageCustomer::write_room(std::map<string, string> &ctx, const DBRoom &room) {
    ctx["room_name"] = room.room_name;
    /// Добавление всей информации комнаты
}

void PageCustomer::write_info_tag(std::map<string, string> &ctx, const DBRoom &room, string tag) {

}

string PageCustomer::get_server_err() {
    Context context = {{"page", "500"}};
    return PageManager::view_.render(context);
}
