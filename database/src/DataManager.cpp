//
// Created by Иван on 24.11.2020.
//

#include "../include/DataManager.h"

DataManager::DataManager() :
    database(std::make_shared<PostgreDBWrapper>()),
    storage(std::make_shared<AmazonS3StorageWrapper>())
{

}

DataManager& DataManager::getInstance() {
    static DataManager instance;
    return instance;
}

shared_ptr<DBUser> DataManager::get_user_info(const int &user_id, ErrorCodes &error) const {
    return database->get_user_info(user_id, error);
}

shared_ptr<DBUser> DataManager::get_user_info(const string &nickname, ErrorCodes &error) const {
    return database->get_user_info(nickname, error);
}

bool DataManager::remove_user(const int& user_id, ErrorCodes &error) const {
    return database->remove_user(user_id, error);
}

bool DataManager::add_user(const DBUser::User &user_info, ErrorCodes &error) const {
    return database->add_user(user_info, error);
}

bool DataManager::edit_user(const int& user_id, const DBUser::User &user, ErrorCodes &error) const {
    return database->edit_user(user_id, user, error);
}

std::optional< vector<pair<DBRoom, Rights>> > DataManager::get_user_rooms(const int &user_id, ErrorCodes &error) const {
    return database->get_user_rooms(user_id, error);
}

shared_ptr<DBRoom> DataManager::get_room_info(const int &room_id, ErrorCodes &error) const {
    return database->get_room_info(room_id, error);
}

bool DataManager::add_room(const DBRoom::Room &room_info, ErrorCodes &error) const {
    return database->add_room(room_info, error);
}

bool DataManager::remove_room(const int& room_id, ErrorCodes &error) const {
    return database->remove_room(room_id, error);
}

bool DataManager::edit_room(const int &room_id, const DBRoom::Room &room, ErrorCodes &error) const {
    return database->edit_room(room_id, room, error);
}

bool DataManager::add_user_to_room(const int &room_id, const int &user_id, Rights user_rights, ErrorCodes &error) const {
    return database->add_user_to_room(room_id, user_id, user_rights, error);
}

bool DataManager::remove_user_from_room(const int &room_id, const int &user_id, ErrorCodes &error) const {
    return database->remove_user_from_room(room_id, user_id, error);
}

std::optional<vector<pair<DBUser, Rights>>> DataManager::get_room_users(const int &room_id, ErrorCodes &error) const {
    return database->get_room_users(room_id, error);
}


std::optional<vector<DBTag>> DataManager::get_room_tags(const int &room_id, ErrorCodes &error) const {
    return database->get_room_tags(room_id, error);
}

std::optional<vector<DBPost>> DataManager::get_room_posts(const int &room_id, ErrorCodes &error) const {
    return database->get_room_posts(room_id, error);
}

bool DataManager::add_post(const DBPost::Post &post_info, ErrorCodes &error) const {
    return database->add_post(post_info, error);
}

bool DataManager::remove_post(const int &post_id, ErrorCodes &error) const {
    return database->remove_post(post_id, error);
}

bool DataManager::edit_post(const int &post_id, const DBPost::Post &post, ErrorCodes &error) const {
    return database->edit_post(post_id, post, error);
}

shared_ptr<DBPost> DataManager::get_post_info(const int &post_id, ErrorCodes &error) const {
    return database->get_post_info(post_id, error);
}







