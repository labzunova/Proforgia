//
// Created by sergei on 28.11.2020.
//

#include "ActivityCustomer.h"

ActivityManager::Status ActivityCustomer::exit() {
    return CLIENT_ERROR;
}

ActivityManager::Status ActivityCustomer::add_room() {
    return CLIENT_ERROR;
}

ActivityManager::Status ActivityCustomer::add_content() {
    return CLIENT_ERROR;
}

ActivityManager::Status ActivityCustomer::create_room() {
    return CLIENT_ERROR;
}

ActivityManager::Status ActivityCustomer::remove_room() {
    return CLIENT_ERROR;
}

ActivityManager::Status ActivityCustomer::add_favorite() {
    return CLIENT_ERROR;
}

ActivityManager::Status ActivityCustomer::add_deadline() {
    return CLIENT_ERROR;
}

ActivityCustomer::ActivityCustomer(std::map<string, string> &context,const User &user)
        : ActivityManager(context)
        , user_(user) {}

void ActivityCustomer::delete_session() {

}

void ActivityCustomer::add_tags_room() {

}
