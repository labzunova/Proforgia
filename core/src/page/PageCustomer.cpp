//
// Created by sergei on 28.11.2020.
//

#include "PageCustomer.h"

#include <utility>
#include <boost/lexical_cast.hpp>

PageCustomer::PageCustomer(std::shared_ptr<DBUser>& user) {
    user_ = user;
}


std::string PageCustomer::get_profile_page() {
    std::string page = "profile";
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

std::string PageCustomer::get_room_page(std::string id) {
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
std::string PageCustomer::get_favorite_page() {
    return get_profile_page();
}

// TODO пока не известно будет ли это в проекте
std::string PageCustomer::get_deadline_page() {
    return get_profile_page();
}

std::string PageCustomer::get_signup_page() {
    return get_profile_page();
}

std::string PageCustomer::get_login_page() {
    return get_profile_page();
}

std::string PageCustomer::get_info_tags(std::string id_room, std::unique_ptr<std::vector<std::string>> tags) {
    return "fdfdsgdsfgdsfgdfgdsfgsdfgdfglgiggglkdfsj";
}

std::string PageCustomer::get_not_found() {
    std::string page = "not_found";
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

void PageCustomer::write_info_tag(Context &ctx, const DBRoom &room, std::string tag) {

}

std::string PageCustomer::get_server_err() {
    std::string page = "500";
    Context context(page);
    TemplateWrapper view(context);
    return view.getHTML();
}
