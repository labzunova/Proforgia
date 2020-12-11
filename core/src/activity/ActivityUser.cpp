//
// Created by sergei on 28.11.2020.
//

#include "ActivityUser.h"

ActivityManager::Status ActivityUser::signUp() {
    if(!validate_signUp())
        return CLIENT_ERROR;

    std::string login = context_["login"];
    std::string email = context_["email"];
    std::string password = context_["password"]; // TODO кодирование пароля
    typename DBUser::User user(email, login, password);
    int id = DBUser::add(user); // TODO проверка на то прошло ли сохранение

    string session = create_session(id);
    context_["session"] = session;
    return OK;
}

ActivityManager::Status ActivityUser::signIn() {
    if(!validate_signIn())
        return CLIENT_ERROR;

    string login = context_["login"];
    string password = context_["password"]; // TODO кодирование
    ErrorCodes er;
    DBUser user = DBUser::get(login, er); // TODO проверка на то пришел ли User
    if(user.password != password)
        return CLIENT_ERROR;

    string session = create_session(user.id);
    context_["session"] = session;
    return OK;
}

ActivityUser::ActivityUser(Context &context) : ActivityManager(context) {
}

bool ActivityUser::validate_signUp() {
    // TODO добавить еще разные проверки
    auto end = context_.end();
    if((context_.find("login") == end) ||
        (context_.find("password") == end) ||
        (context_.find("email") == end))

        return false;

    return true;
}


string ActivityUser::create_session(const int& id) {
    string session_str; // TODO генерируем стоку сессии
    typename DBSession::Session session(id, session_str);
    DBSession::add(session);
}

bool ActivityUser::validate_signIn() {
    // TODO добавить еще разные проверки
    auto end = context_.end();
    if((context_.find("login") == end) ||
       (context_.find("password") == end))

        return false;

    return true;
}
