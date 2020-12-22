//
// Created by sergei on 28.11.2020.
//

#include "PageCustomer.h"

#include <utility>
#include <boost/lexical_cast.hpp>

PageCustomer::PageCustomer(std::shared_ptr<DBUser>& user) {
    user_ = user;
}


PageManager::Status PageCustomer::get_profile_page(std::string& body) {
    std::string page = "profile";
    Context context(page);

    // запись user в context
    Context::User user;
    write_user(user);

    // берем все комнаты из бд
    ErrorCodes er;
    auto db_rooms = user_->get_rooms(er);
    if (!db_rooms) {
        return SERVER_ERROR;
    }

    // room bd -> room context
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
    body = view.getHTML();
    return OK;
}

// TODO обработака ErrorCodes
PageManager::Status PageCustomer::get_room_page(std::string& body, std::string id) {
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
        return CLIENT_ERROR_VALID;
    }
    ErrorCodes er;

    // запись room в context
    auto db_room = DBRoom::get(id_room, er);
    if (!db_room) {
        if (er == DB_ENTITY_NOT_FOUND)
            return CLIENT_ERROR_VALID;
        else
            return SERVER_ERROR;
    }
    Context::Room room;
    write_room(room, db_room);

    // запись tags в context
    auto db_tags = db_room->get_tags(er);
    if (!db_tags)
        return SERVER_ERROR;

    std::vector<Context::Tag> tags;
    PageCustomer::set_tags(db_tags.value(), tags);

    // запись posts в context
    auto db_posts = db_room->get_posts(er);
    if (!db_posts)
        return SERVER_ERROR;

    std::vector<Context::Post> posts;
    PageCustomer::set_posts(db_posts.value(), posts);

    context.setMainContext(user, room, tags, posts);
    TemplateWrapper view(context);
    body = view.getHTML();
    return OK;
}


void PageCustomer::set_tags(std::vector<DBTag>& input, std::vector<Context::Tag>& output) {
    for (const auto& db_tag : input) {
        Context::Tag tag;
        tag.tag = db_tag.getName();
        tag.url = std::to_string(db_tag.get_id());
        output.push_back(std::move(tag));
    }
}

void PageCustomer::set_files(std::vector<DBPost::FileData>& input, std::vector<Context::File>& output) {
    for (const auto& db_file : input) {
        Context::File file;
        file.filename = db_file.client_filename;
        file.url = db_file.storage_link;
        file.type = (db_file.fileType == DBPost::IMAGE) ? Context::File::IMAGE : Context::File::FILE;
        output.push_back(std::move(file));
    }
}

void PageCustomer::set_posts(std::vector<DBPost>& input, std::vector<Context::Post>& output) {
    for (auto& db_post : input) {
        ErrorCodes er;

        Context::Post post;
        if (db_post.title == DEFAULT_TITLE) // не отображаем дефолтные посты
            continue;

        post.title = db_post.title;
        auto db_tags = db_post.get_tags(er).value(); // TODO обработать ошибку
        PageCustomer::set_tags(db_tags, post.tags);
        post.text = db_post.text;
        post.author = db_post.get_author(er)->nick_name;
        // TODO fileUrls
        auto db_files = db_post.get_attachments(er);
        if (db_files)
            PageCustomer::set_files(db_files.value(), post.files);
        output.push_back(std::move(post));
    }
}

PageManager::Status PageCustomer::get_add_content_page(std::string& body, std::string& id, std::string& id_post) {
    std::string page = "add";
    Context context(page);

    // запись user в context
    Context::User user;
    write_user(user);

    int id_room = 0;
    try {
        id_room = boost::lexical_cast<int>(id);
    }
    catch (boost::bad_lexical_cast) {
        return CLIENT_ERROR_VALID;
    }
    ErrorCodes er;

    // запись room в context
    auto db_room = DBRoom::get(id_room, er);
    if (!db_room) {
        if (er == DB_ENTITY_NOT_FOUND)
            return CLIENT_ERROR_VALID;
        else
            return SERVER_ERROR;
    }
    Context::Room room;
    write_room(room, db_room);

    // запись tags в context
    auto db_tags = db_room->get_tags(er);
    if (!db_tags)
        return SERVER_ERROR;

    std::vector<Context::Tag> tags;
    PageCustomer::set_tags(db_tags.value(), tags);

    // TODO жду ваню, когда он будет возвращать id при создании
    // берем из куки id post если есть, если нет создаем новый
    int id_post_db = 0;
    if (id_post.empty()) { // создаем новый пост

        typename DBPost::Post post(id_room, user_->get_id(), DEFAULT_TITLE, DEFAULT_TEXT);

        id_post_db = DBPost::add(post, er);
        id_post = std::to_string(id_post_db); // чтобы добавить потом в сессию (в Handler)
    }
    else {
        try {
            id_post_db = boost::lexical_cast<int>(id_post);
        }
        catch (boost::bad_lexical_cast) {
            return CLIENT_ERROR_VALID;
        }
    }


    auto db_post = DBPost::get(id_post_db, er);
    if (!db_post)
        return SERVER_ERROR;

    auto links = DBPost::get_upload_link(id_post_db, er);
    if (!links)
        return SERVER_ERROR;

    context.setAddContext(user, room, tags, links->first, links->second);

    TemplateWrapper view(context);
    body = view.getHTML();
    return OK;
}

// TODO пока не известно будет ли это в проекте
PageManager::Status PageCustomer::get_favorite_page(std::string& body) {
    return CLIENT_ERROR_VALID;
}

// TODO пока не известно будет ли это в проекте
PageManager::Status PageCustomer::get_deadline_page(std::string& body) {
    return CLIENT_ERROR_VALID;
}

PageManager::Status PageCustomer::get_info_tags(std::string& body, std::string id, std::unique_ptr<std::vector<std::string>> tags) {
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
        return CLIENT_ERROR_VALID;
    }
    ErrorCodes er;

    // запись room в context
    auto db_room = DBRoom::get(id_room, er);
    if (!db_room) {
        if (er == DB_ENTITY_NOT_FOUND)
            return CLIENT_ERROR_VALID;
        else
            return SERVER_ERROR;
    }

    Context::Room room;
    write_room(room, db_room);

    // запись tags в context
    auto db_tags = db_room->get_tags(er);
    if (!db_tags)
        return SERVER_ERROR;

    std::vector<Context::Tag> new_tags;
    PageCustomer::set_tags(db_tags.value(), new_tags);

    // запись posts в context
    auto db_posts = DBPost::get(*tags, id_room, er);
    if (!db_posts)
        return SERVER_ERROR;

    std::vector<Context::Post> posts;
    PageCustomer::set_posts(db_posts.value(), posts);

    int id_tag = 0;
    try {
        id_tag = boost::lexical_cast<int>((*tags)[0]);
    }
    catch (boost::bad_lexical_cast) {
        return CLIENT_ERROR_VALID;
    }

    shared_ptr<DBTag> tag_cur_db = DBTag::get(id_tag, er);
    if (!tag_cur_db) {
        if (er == DB_ENTITY_NOT_FOUND)
            return CLIENT_ERROR_VALID;
        else
            return SERVER_ERROR;
    }

    Context::Tag tag_cur;
    tag_cur.tag = tag_cur_db->getName();
    tag_cur.url = std::to_string(tag_cur_db->get_id());

    context.setTagContext(user, room, new_tags, posts, tag_cur);
    TemplateWrapper view(context);
    body = view.getHTML();
    return OK;
}

PageManager::Status PageCustomer::get_not_found(std::string& body) {
    std::string page = "not_found";
    Context context(page);
    TemplateWrapper view(context);
    body = view.getHTML();
    return OK;
}

void PageCustomer::write_user(Context::User &user) {
    user.username = user_->nick_name;
    user.avatarUrl = "/34534534";  // TODO берем из юзера эту информацию, когда будет в бд это
}

void PageCustomer::write_room(Context::Room &room, const std::shared_ptr<DBRoom> &db_room) {
    room.title = db_room->room_name;
    room.url = std::to_string(db_room->get_id());
}

PageManager::Status PageCustomer::get_server_err(std::string& body) {
    std::string page = "500";
    Context context(page);
    TemplateWrapper view(context);
    body = view.getHTML();
    return OK;
}
