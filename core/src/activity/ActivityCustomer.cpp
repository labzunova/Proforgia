//
// Created by sergei on 28.11.2020.
//

#include "ActivityCustomer.h"

#include <utility>
#include <boost/lexical_cast.hpp>

template<class User, class Room, class Session>
ActivityManager::Status ActivityCustomer<User, Room, Session>::exit() {
    string session = context_["SESSION"];
    Session::remove(session);
    return CLIENT_ERROR;
}

template<class User, class Room, class Session>
ActivityManager::Status ActivityCustomer<User, Room, Session>::add_room() {
    if(context_.find("ID_ROOM") == context_.end())
        return CLIENT_ERROR;
    int id_room = boost::lexical_cast<int>(context_["ID_ROOM"]); /// возможно какой то другой индификатор который вводит пользователь
    Room room = Room::get(id_room); // TODO проверка существует ли комната
    room.add_user(user_.id);
    user_.add_room(id_room);
    user_.update(); // TODO проверка прошло ли сохранение
    return OK;
}

// TODO пока не понятно в каком виде придут данные
template<class User, class Room, class Session>
ActivityManager::Status ActivityCustomer<User, Room, Session>::add_content() {
    return CLIENT_ERROR;
}

template<class User, class Room, class Session>
ActivityManager::Status ActivityCustomer<User, Room, Session>::create_room() {
    if(context_.find("NAME_ROOM") == context_.end())
        return CLIENT_ERROR;

    typename Room::Room room(context_["NAME_ROOM"]);
    int id_room = room.add(room); // TODO проверка на ошибку добавления
    // TODO возможно выделение админа как то отдельно в комнате
    Room::add_user(id_room, user_.id); // TODO проверка на ошибку добавления
    User::add_room(user_.id, id_room); // TODO проверка прошло ли сохранение

    return OK;
}

template<class User, class Room, class Session>
ActivityManager::Status ActivityCustomer<User, Room, Session>::remove_room() {
    if(context_.find("NAME_ROOM") == context_.end())
        return CLIENT_ERROR;

    /// возможно какая то проверка, есть ли права у пользователя на удаление

    int id_room = boost::lexical_cast<int>(context_["ID_ROOM"]);
    Room room = Room::get(id_room);
    // TODO удаление комнаты у всех ее user
    Room::remove(id_room); // TODO проверка прошло ли удаление

    return OK;
}

/// Пока не понятно буддет ли эта возможность в итоговом проекте
template<class User, class Room, class Session>
ActivityManager::Status ActivityCustomer<User, Room, Session>::add_favorite() {
    return CLIENT_ERROR;
}

/// Пока не понятно буддет ли эта возможность в итоговом проекте
template<class User, class Room, class Session>
ActivityManager::Status ActivityCustomer<User, Room, Session>::add_deadline() {
    return CLIENT_ERROR;
}

template<class User, class Room, class Session>
ActivityCustomer<User, Room, Session>::ActivityCustomer(Context &context, User user)
        : ActivityManager(context)
        , user_(std::move(user)) {}

