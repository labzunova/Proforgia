//
// Created by sergei on 28.11.2020.
//

#include "ActivityCustomer.h"

#include <utility>
#include <boost/lexical_cast.hpp>

ActivityManager::Status ActivityCustomer::exit() {
    std::string session = context_["session"];
    //DBSession::remove(session);
    return CLIENT_ERROR;
}

ActivityManager::Status ActivityCustomer::add_room() {
    context_["roomID"] = "1"; //// заглушка
    if(context_.find("roomID") == context_.end())
        return CLIENT_ERROR;
    int id_room = boost::lexical_cast<int>(context_["roomID"]); /// возможно какой то другой индификатор который вводит пользователь
    ErrorCodes er;
    auto room = DBRoom::get(id_room, er); // TODO проверка существует ли комната
    if (!room) {
        if (er == DB_ENTITY_NOT_FOUND)
            return CLIENT_ERROR;
        else
            return SERVER_ERROR;
    }

    DBRoom::add_user(id_room, user_->get_id(), MEMBER, er);
//    if (er)   // TODO другая проверка на er
//        return SERVER_ERROR;

    return OK;
}

// TODO пока не понятно в каком виде придут данные
ActivityManager::Status ActivityCustomer::add_content() {
    return CLIENT_ERROR;
}

ActivityManager::Status ActivityCustomer::create_room() {
    context_["title"] = "room1"; //// заглушка
    if(context_.find("title") == context_.end())
        return CLIENT_ERROR;

    typename DBRoom::Room room(context_["title"]);

    ErrorCodes er;
    bool code = DBRoom::add(room, er);
    if (!code)
        return SERVER_ERROR;

//    DBRoom::add_user()  // TODO добавление пользвателя в room
    //int id_room = room.add(room); // TODO проверка на ошибку добавления
    // TODO возможно выделение админа как то отдельно в комнате

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

