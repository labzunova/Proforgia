//
// Created by sergei on 28.11.2020.
//

#include "ActivityCustomer.h"

#include <utility>
#include <boost/lexical_cast.hpp>

ActivityManager::Status ActivityCustomer::exit() {
    std::string session = context_["session"];

    ErrorCodes er;
    DBSession::remove(session, er);

    return CLIENT_ERROR;
}

ActivityManager::Status ActivityCustomer::exit_room() {
    if(context_.find("roomID") == context_.end())
        return CLIENT_ERROR;

    int id_room = 0;
    try {
        id_room = boost::lexical_cast<int>(context_["roomID"]);
    }
    catch (boost::bad_lexical_cast) {
        return CLIENT_ERROR;
    }

    ErrorCodes er;
    auto room = DBRoom::get(id_room, er);
    if (!room) {
        if (er == DB_ENTITY_NOT_FOUND)
            return CLIENT_ERROR;
        else
            return SERVER_ERROR;
    }

    bool valid = DBRoom::remove_user(id_room, user_->get_id(), er);
    if (!valid)
        return SERVER_ERROR;

    return OK;
}

ActivityManager::Status ActivityCustomer::add_room() {
    if(context_.find("roomID") == context_.end())
        return CLIENT_ERROR;

    int id_room = 0;
    try {
        id_room = boost::lexical_cast<int>(context_["roomID"]); /// возможно какой то другой индификатор который вводит пользователь
    }
    catch (boost::bad_lexical_cast) {
        return CLIENT_ERROR;
    }
    ErrorCodes er;
    auto room = DBRoom::get(id_room, er);
    if (!room) {
        if (er == DB_ENTITY_NOT_FOUND)
            return CLIENT_ERROR;
        else
            return SERVER_ERROR;
    }

    bool valid = DBRoom::add_user(id_room, user_->get_id(), MEMBER, er);
    if (!valid)
        return SERVER_ERROR;

    return OK;
}

ActivityManager::Status ActivityCustomer::add_content() {
    // TODO подумать надо ли проверять что существует данная комнта (наверное да)

    int id_post = 0, id_room = 0;
    try {
        id_post = boost::lexical_cast<int>(context_["postID"]);
        id_room = boost::lexical_cast<int>(context_["room"]);
    }
    catch (boost::bad_lexical_cast) {
        return CLIENT_ERROR;
    }

    ErrorCodes er;
    auto db_post = DBPost::get(id_post, er);
    if (!db_post)
        return SERVER_ERROR;

    db_post->title = context_["title"];
    db_post->text = context_["text"];
    db_post->room_id = id_room;
    bool valid = db_post->update(er);
    if (!valid)
        return SERVER_ERROR;
//    typename DBPost::Post post(id_room, user_->get_id(), context_["title"], context_["text"]);

    // добавление в бд поста
//    bool valid = DBPost::add(post, er);
//    if (!valid) {
//        return SERVER_ERROR;
//    }

    // добавление файлов в бд
    if (!context_["file_name"].empty()) {
        auto valid = DBPost::add_file_to_db(context_["file_name"],
                               context_["file_name_db"],
                               id_post,
                               (type_is(context_["file_name"]) == IMAGE) ? DBPost::IMAGE : DBPost::FILE,
                               er);

        if(!valid)
            return SERVER_ERROR;
    }

    // добавление tag в бд
    std::vector<std::string> tags;
    tags.push_back(context_["tag"]);
    valid = db_post->update_tags(tags, er);
    if (!valid)
        return SERVER_ERROR;

    return OK;
}

ActivityManager::Type ActivityCustomer::type_is(const std::string& file_name) {
    std::string extension = file_name.substr(file_name.find('.'));
    boost::algorithm::to_lower(extension);
    if ((extension == ".jpeg") ||
        (extension == ".jpg") ||
        (extension == ".png"))
        return IMAGE;
    else
        return FILE;
}

ActivityManager::Status ActivityCustomer::create_room() {
    if(context_.find("title") == context_.end())
        return CLIENT_ERROR;

    typename DBRoom::Room room(context_["title"]);

    ErrorCodes er;
    int id_room = DBRoom::add(room, er);
    if (!id_room)
        return SERVER_ERROR;

    bool valid = DBRoom::add_user(id_room, user_->get_id(), ADMIN, er);
    if (!valid)
        return SERVER_ERROR;

    return OK;
}

ActivityManager::Status ActivityCustomer::remove_room() {
    if(context_.find("title") == context_.end())
        return CLIENT_ERROR;

    /// возможно какая то проверка, есть ли права у пользователя на удаление

    int id_room = boost::lexical_cast<int>(context_["title"]);
    ErrorCodes er;
    auto room = DBRoom::get(id_room, er);
    // TODO удаление комнаты у всех ее user
    //DBRoom::remove(id_room); // TODO проверка прошло ли удаление

    return OK;
}

/// Пока не понятно буддет ли эта возможность в итоговом проекте
ActivityManager::Status ActivityCustomer::add_favorite() {
    return CLIENT_ERROR;
}

/// Пока не понятно буддет ли эта возможность в итоговом проекте
ActivityManager::Status ActivityCustomer::add_deadline() {
    return CLIENT_ERROR;
}

ActivityCustomer::ActivityCustomer(ContextMap &context, shared_ptr<DBUser> user)
        : ActivityManager(context)
        , user_(user) {}


