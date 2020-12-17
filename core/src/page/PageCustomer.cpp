//
// Created by sergei on 28.11.2020.
//

#include "PageCustomer.h"

#include <utility>
#include <boost/lexical_cast.hpp>

/// поработать над ContextMap

PageCustomer::PageCustomer(std::shared_ptr<DBUser>& user) {
    user_ = user;
}


string PageCustomer::get_profile_page() {
    string page = "profile";
    Context context(page);
    Context::User user;

    user.username = user_->nick_name;
    user.avatarUrl = "/34534534";  // TODO берем из юзера эту информацию, когда будет в бд это

    // TODO правильно преобразовать одно в другое
    ErrorCodes er;
    auto db_rooms = user_->get_rooms(er);
    vector<Context::Room> room;

    context.setProfileContext(user, room);

    TemplateWrapper view(context);
    return view.getHTML();
}

string PageCustomer::get_room_page(string id) {
    string page = "room";
    Context context(page);
    write_user(context);

    int id_room = boost::lexical_cast<int>(id);
    ErrorCodes er;
    write_room(context, *DBRoom::get(id_room, er));
    TemplateWrapper view(context);
    return view.getHTML();
}

// TODO пока не известно будет ли это в проекте
string PageCustomer::get_favorite_page() {
    return get_profile_page();
}

// TODO пока не известно будет ли это в проекте
string PageCustomer::get_deadline_page() {
    return get_profile_page();
}

string PageCustomer::get_signup_page() {
    return get_profile_page();
}

string PageCustomer::get_login_page() {
    return get_profile_page();
}

string PageCustomer::get_info_tags(string id_room, std::unique_ptr<std::vector<string>> tags) {
    return "fdfdsgdsfgdsfgdfgdsfgsdfgdfglgiggglkdfsj";
}

string PageCustomer::get_not_found() {
    string page = "not_found";
    Context context(page);
    TemplateWrapper view(context);
    return view.getHTML();
}

void PageCustomer::write_user(Context &ctx) {
    ctx.user.username = user_->nick_name;
    ctx.user.avatarUrl = "/34534534";  // TODO берем из юзера эту информацию, когда будет в бд это
}

void PageCustomer::write_room(Context &ctx, const DBRoom &room) {
//    ctx["room_name"] = room.room_name;
    /// Добавление всей информации комнаты
}

void PageCustomer::write_info_tag(Context &ctx, const DBRoom &room, string tag) {

}

string PageCustomer::get_server_err() {
    string page = "500";
    Context context(page);
    TemplateWrapper view(context);
    return view.getHTML();
}
