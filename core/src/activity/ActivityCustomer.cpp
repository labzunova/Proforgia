//
// Created by sergei on 28.11.2020.
//

#include "ActivityCustomer.h"

#include <utility>
#include <boost/lexical_cast.hpp>

ActivityManager::Status ActivityCustomer::exit() {
    string session = context_["session"];
    //DBSession::remove(session);
    return CLIENT_ERROR;
}

ActivityManager::Status ActivityCustomer::add_room() {
    if(context_.find("id_room") == context_.end())
        return CLIENT_ERROR;
    int id_room = boost::lexical_cast<int>(context_["id_room"]); /// возможно какой то другой индификатор который вводит пользователь
    ErrorCodes er;
    auto room = DBRoom::get(id_room, er); // TODO проверка существует ли комната
    //room->add_user(user_.id);
    //user_.add_room(id_room);
    //user_.update(); // TODO проверка прошло ли сохранение
    return OK;
}

// TODO пока не понятно в каком виде придут данные
ActivityManager::Status ActivityCustomer::add_content() {
    return CLIENT_ERROR;
}

ActivityManager::Status ActivityCustomer::create_room() {
    if(context_.find("name_room") == context_.end())
        return CLIENT_ERROR;

    typename DBRoom::Room room(context_["name_room"]);
    //int id_room = room.add(room); // TODO проверка на ошибку добавления
    // TODO возможно выделение админа как то отдельно в комнате
    //DBRoom::add_user(id_room, user_.id); // TODO проверка на ошибку добавления
    //DBUser::add_room(user_.id, id_room); // TODO проверка прошло ли сохранение

    return OK;
}

ActivityManager::Status ActivityCustomer::remove_room() {
    if(context_.find("name_room") == context_.end())
        return CLIENT_ERROR;

    /// возможно какая то проверка, есть ли права у пользователя на удаление

    int id_room = boost::lexical_cast<int>(context_["id_room"]);
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

ActivityCustomer::ActivityCustomer(Context &context, DBUser user)
        : ActivityManager(context)
        , user_(user) {}

