//
// Created by Иван on 24.11.2020.
//

#include "../include/DataManager.h"

DataManager::DataManager() {
    // TODO: create database and storage instances
}

DataManager& DataManager::getInstance() {
    static DataManager instance;
    return instance;
}

std::string DataManager::add_user(const User &user_info, ErrorCodes &error) const {
    return nullptr;
}

std::string DataManager::add_room(const Room &room_info, ErrorCodes &error) const {
    return nullptr;
}

std::string DataManager::add_post(const Post &post_info, ErrorCodes &error) const {
    return nullptr;
}

std::string DataManager::add_session(const Session &session_info, ErrorCodes &error) const {
    return nullptr;
}

bool DataManager::add_user_to_room(const std::string &room_id, const std::string &user_id, ErrorCodes &error) const {
    return false;
}

bool DataManager::add_discipline(const std::string &discipline_name, const std::string &room_id,
                                 const std::string &user_id) const {
    return false;
}

bool DataManager::add_category(const std::string &category_name, const std::string &discipline_name,
                               const std::string &room_id, const std::string &user_id) const {
    return false;
}

bool DataManager::remove_user(const std::string &user_id, ErrorCodes &error) const {
    return false;
}

bool DataManager::remove_room(const std::string &room_id, ErrorCodes &error) const {
    return false;
}

bool DataManager::remove_post(const std::string &post_id, ErrorCodes &error) const {
    return false;
}

bool DataManager::remove_user_from_room(const std::string &room_id, const std::string &user_id, ErrorCodes &error) const {
    return false;
}

bool DataManager::remove_session(const std::string &session_id, ErrorCodes &error) {
    return false;
}

DBUser DataManager::get_user_info(const std::string &user_id) const {
    return DBUser();
}

DBRoom DataManager::get_room_info(const std::string &room_id) const {
    return DBRoom();
}

DBPost DataManager::get_post_info(const std::string &post_id) const {
    return DBPost();
}

DBSession DataManager::get_session_info(const std::string &session_id) const {
    return DBSession();
}

bool DataManager::edit_user(const std::string &user_id, const User &user_info) const {
    return false;
}

bool DataManager::edit_room(const std::string &room_id, const Room &room_info) const {
    return false;
}

bool DataManager::edit_post(const std::string &post_id, const Post &post_info) const {
    return false;
}

