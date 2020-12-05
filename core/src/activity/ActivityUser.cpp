//
// Created by sergei on 28.11.2020.
//

#include "ActivityUser.h"

template<class User, class Session>
ActivityManager::Status ActivityUser<User, Session>::signUp() {
    return CLIENT_ERROR;
}

template<class User, class Session>
ActivityManager::Status ActivityUser<User, Session>::signIn() {
    return CLIENT_ERROR;
}

template<class User, class Session>
ActivityUser::ActivityUser(std::map<string, string> &context) : ActivityManager(context) {

}

template<class User, class Session>
bool ActivityUser::is_email(const string &email) const {
    return false;
}

template<class User, class Session>
User ActivityUser::get_user(const string &email, const string &password) {
    return User();
}

template<class User, class Session>
User ActivityUser::create_user(const std::map<string, string> &info) {
    return User();
}

template<class User, class Session>
Session ActivityUser::create_session(const User &user) {
    return Session();
}
