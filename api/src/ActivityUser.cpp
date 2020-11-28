//
// Created by sergei on 28.11.2020.
//

#include "ActivityUser.h"

ActivityManager::Status ActivityUser::signUp() {
    return CLIENT_ERROR;
}

ActivityManager::Status ActivityUser::signIn() {
    return CLIENT_ERROR;
}

ActivityUser::ActivityUser(std::map<string, string> &context) : ActivityManager(context) {

}

bool ActivityUser::is_email(const string &email) const {
    return false;
}

User ActivityUser::get_user(const string &email, const string &password) {
    return User();
}

User ActivityUser::create_user(const std::map<string, string> &info) {
    return User();
}

Session ActivityUser::create_session(const User &user) {
    return Session();
}
