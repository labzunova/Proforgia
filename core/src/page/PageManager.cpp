//
// Created by sergei on 20.12.2020.
//

#include "PageManager.h"

PageManager::Status PageManager::get_profile_page(std::string &body) {
    return PageManager::CLIENT_ERROR_RIGHT;
}

PageManager::Status PageManager::get_room_page(std::string &body, std::string id_room) {
    return PageManager::CLIENT_ERROR_RIGHT;
}

PageManager::Status PageManager::get_add_content_page(std::string &body, std::string& id_room, std::string& id_post) {
    return PageManager::CLIENT_ERROR_RIGHT;
}

PageManager::Status PageManager::get_favorite_page(std::string &body) {
    return PageManager::CLIENT_ERROR_RIGHT;
}

PageManager::Status PageManager::get_deadline_page(std::string &body) {
    return PageManager::CLIENT_ERROR_RIGHT;
}

PageManager::Status PageManager::get_signup_page(std::string &body) {
    return PageManager::CLIENT_ERROR_RIGHT;
}

PageManager::Status PageManager::get_login_page(std::string &body) {
    return PageManager::CLIENT_ERROR_RIGHT;
}

PageManager::Status
PageManager::get_info_tags(std::string &body, std::string id_room, std::unique_ptr<std::vector<std::string>> tags) {
    return PageManager::CLIENT_ERROR_RIGHT;
}

PageManager::Status PageManager::get_not_found(std::string &body) {
    return PageManager::CLIENT_ERROR_RIGHT;
}

PageManager::Status PageManager::get_server_err(std::string &body) {
    return PageManager::CLIENT_ERROR_RIGHT;
}
