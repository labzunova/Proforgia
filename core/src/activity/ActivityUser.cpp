//
// Created by sergei on 28.11.2020.
//

#include "ActivityUser.h"

template<class User, class Session>
ActivityManager::Status ActivityUser<User, Session>::signUp() {
    if(!validate_signUp())
        return CLIENT_ERROR;

    std::string login = context_["login"];
    std::string email = context_["email"];
    std::string password = context_["password"]; // TODO кодирование пароля
    typename User::User user(email, login, password);
    int id = User::add(user); // TODO проверка на то прошло ли сохранение

    string session = create_session(id);
    context_["session"] = session;
    return OK;
}

template<class User, class Session>
ActivityManager::Status ActivityUser<User, Session>::signIn() {
    if(!validate_signIn())
        return CLIENT_ERROR;

    string login = context_["login"];
    string password = context_["password"]; // TODO кодирование
    User user = User::get(login); // TODO проверка на то пришел ли User
    if(user.password != password)
        return CLIENT_ERROR;

    string session = create_session(user.id);
    context_["session"] = session;
    return OK;
}

template<class User, class Session>
ActivityUser<User, Session>::ActivityUser(Context &context) : ActivityManager(context) {
}

template<class User, class Session>
bool ActivityUser<User, Session>::validate_signUp() {
    // TODO добавить еще разные проверки
    auto end = context_.end();
    if((context_.find("login") == end) ||
        (context_.find("password") == end) ||
        (context_.find("email") == end))

        return false;

    return true;
}


template<class User, class Session>
string ActivityUser<User, Session>::create_session(const int& id) {
    string session_str; // TODO генерируем стоку сессии
    typename Session::Session session(id, session_str);
    Session::add(session);
}

template<class User, class Session>
bool ActivityUser<User, Session>::validate_signIn() {
    // TODO добавить еще разные проверки
    auto end = context_.end();
    if((context_.find("login") == end) ||
       (context_.find("password") == end))

        return false;

    return true;
}
