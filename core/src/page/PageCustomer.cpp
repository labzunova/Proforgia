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

    // запись user в context
    Context::User user;
    user.username = user_->nick_name;
    user.avatarUrl = "/34534534";  // TODO берем из юзера эту информацию, когда будет в бд это

    ErrorCodes er;
    auto db_rooms = user_->get_rooms(er);
    vector<Context::Room> rooms;
    for (int i = 0; i < db_rooms->size(); ++i) {
        auto db_room = db_rooms.value()[i].first;
        Context::Room room;
        room.title = db_room.room_name;
        room.url = std::to_string(db_room.get_id());
        rooms.push_back(std::move(room));
    }

    context.setProfileContext(user, rooms);

    TemplateWrapper view(context);
    return view.getHTML();
}

// TODO обработака ErrorCodes
std::string PageCustomer::get_room_page(std::string id) {
    string page = "main";
    Context context(page);

    // запись user в context
    Context::User user;
    write_user(user);

    int id_room = 0;
    try {
        id_room = boost::lexical_cast<int>(id);
    }
    catch (boost::bad_lexical_cast) {
        return "";
    }
    ErrorCodes er;

    // запись room в context
    auto db_room = DBRoom::get(id_room, er);

    // TODO другой обработчик
    if (!db_room) {
        if (er == DB_ENTITY_NOT_FOUND)
            return "";
        else
            return "";
    }
    Context::Room room;
    write_room(room, db_room);

    // запись tags в context
    auto db_tags = db_room->get_tags(er);
    std::vector<Context::Tag> tags;
    PageCustomer::set_tags(db_tags.value(), tags);

    // запись posts в context
    auto db_posts = db_room->get_posts(er);
    std::vector<Context::Post> posts;
    PageCustomer::set_posts(db_posts.value(), posts);

    context.setMainContext(user, room, tags, posts);
    TemplateWrapper view(context);
    return view.getHTML();
}

void PageCustomer::set_tags(std::vector<DBTag>& input, std::vector<Context::Tag>& output) {
    for (const auto& db_tag : input) {
        Context::Tag tag;
        tag.tag = db_tag.getName();
        tag.url = std::to_string(db_tag.get_id());
        output.push_back(std::move(tag));
    }
}

void PageCustomer::set_posts(std::vector<DBPost>& input, std::vector<Context::Post>& output) {
    for (auto& db_post : input) {
        ErrorCodes er;

        Context::Post post;
        post.title = db_post.title;
        auto db_tags = db_post.get_tags(er).value(); // TODO обработать ошибку
        PageCustomer::set_tags(db_tags, post.tags);
        post.text = db_post.text;
        post.author = db_post.get_author(er)->nick_name;
        // TODO fileUrls
        output.push_back(std::move(post));
    }
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

std::string PageCustomer::get_info_tags(std::string id, std::unique_ptr<std::vector<std::string>> tags) {
    string page = "tag";
    Context context(page);

    // запись user в context
    Context::User user;
    write_user(user);

    int id_room = 0;
    try {
        id_room = boost::lexical_cast<int>(id);
    }
    catch (boost::bad_lexical_cast) {
        return "";
    }
    ErrorCodes er;

    // запись room в context
    auto db_room = DBRoom::get(id_room, er);

    // TODO другой обработчик
    if (!db_room) {
        if (er == DB_ENTITY_NOT_FOUND)
            return "";
        else
            return "";
    }
    Context::Room room;
    write_room(room, db_room);

    // запись tags в context
    auto db_tags = db_room->get_tags(er);
    std::vector<Context::Tag> new_tags;
    PageCustomer::set_tags(db_tags.value(), new_tags);

    // запись posts в context
    auto db_posts = DBPost::get(*tags, id_room, er);
    std::vector<Context::Post> posts;
    PageCustomer::set_posts(db_posts.value(), posts);

    int id_tag = 0;
    try {
        id_tag = boost::lexical_cast<int>((*tags)[0]);
    }
    catch (boost::bad_lexical_cast) {
        return "";
    }

    shared_ptr<DBTag> tag_cur_db = DBTag::get(id_tag, er);
    Context::Tag tag_cur;
    tag_cur.tag = tag_cur_db->getName();
    tag_cur.url = std::to_string(tag_cur_db->get_id());

    context.setTagContext(user, room, new_tags, posts, tag_cur);
    TemplateWrapper view(context);
    return view.getHTML();
}

std::string PageCustomer::get_not_found() {
    std::string page = "not_found";
    Context context(page);
    TemplateWrapper view(context);
    return view.getHTML();
}

void PageCustomer::write_user(Context::User &user) {
    user.username = user_->nick_name;
    user.avatarUrl = "/34534534";  // TODO берем из юзера эту информацию, когда будет в бд это
}

void PageCustomer::write_room(Context::Room &room, const std::shared_ptr<DBRoom> &db_room) {
    room.title = db_room->room_name;
    room.url = std::to_string(db_room->get_id());
}

void PageCustomer::write_info_tag(Context &ctx, const DBRoom &room, std::string tag) {

}

std::string PageCustomer::get_server_err() {
    std::string page = "500";
    Context context(page);
    TemplateWrapper view(context);
    return view.getHTML();
}
