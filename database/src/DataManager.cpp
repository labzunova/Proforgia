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


std::optional<vector<DBPost> >
DataManager::get_posts_by_tags(vector<string> &_tags, int room_id, ErrorCodes &error) const {
    auto posts_ids = database->get_posts_by_tags(_tags, room_id, error);
    if (!posts_ids) {
        return std::nullopt;
    }

    ErrorCodes _error;
    vector<DBPost> posts;
    posts.reserve(posts_ids->size());
    for (int i = 0; i < posts_ids->size(); i++) {
        auto post = database->get_post_info(posts_ids.value()[i], _error);
        if (!post) {
            switch (_error) {
                case DB_CONNECTION_ERROR:
                    error = DB_CONNECTION_ERROR;
                    return std::nullopt;
                case DB_ENTITY_NOT_FOUND:
                    continue;
                default:
                    error = UNKNOWN_DB_ERROR;
                    return std::nullopt;
            }
        }
        posts.push_back(post.operator*());
    }

    return posts;
}

bool DataManager::add_tags_to_post(vector<std::string> &_tags, const int &post_id, const int &room_id, ErrorCodes &error) const {
    return database->add_tags_to_post(_tags, post_id, room_id, error);
}

std::string DataManager::get_file_link(const std::string &filename, ErrorCodes &error) const {
    return storage->get_file_link(filename, error);
}

std::string DataManager::get_file_upload_link(const std::string &filename, ErrorCodes &error) const {
    return storage->get_file_upload_link(filename, error);
}

bool DataManager::remove_file_from_storage(const std::string &filename, ErrorCodes &error) const {
    return storage->remove_file_from_storage(filename, error);
}

bool DataManager::add_file(const string& filename, int post_id, ErrorCodes &error) const {
    return database->add_file(filename, post_id, error);
}

shared_ptr<DBTag> DataManager::get_tag_info(const int &tag_id, ErrorCodes &error) const {
    return database->get_tag_info(tag_id, error);
}

std::optional<std::vector<DBTag> > DataManager::get_post_tags(int post_id, ErrorCodes &error) const {
    // взять id всех тэгов этого поста
    auto tags_ids = database->get_post_tags_ids(post_id, error);
    if (!tags_ids)
        return std::nullopt;
    // получить в цикле все тэги по id
    std::vector<DBTag> tags;
    for (int i = 0; i < tags_ids->size(); i++) {
        auto tag = database->get_tag_info(tags_ids.value()[i], error);
        if (!tag)
            return std::nullopt;
        tags.emplace_back(*tag);
    }
    return tags;
}

std::optional<std::vector<std::string> > DataManager::get_post_attachments(int post_id, ErrorCodes &error) const {
    return database->get_post_attachments(post_id, error);
}






