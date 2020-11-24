//
// Created by Иван on 24.11.2020.
//

#include "../include/Wrappers/DBWrapperRealisations/PostgreDBWrapper.h"

bool PostgreDBWrapper::add_file_record(const std::string &file_id, const std::string &filename,
                                       const std::string &file_storage_ref, const std::string &post_id,
                                       ErrorCodes &error) {
    return false;
}

bool PostgreDBWrapper::add_user(const std::string &user_id, const User &user_info, ErrorCodes &error) {
    return false;
}

bool PostgreDBWrapper::add_room(const std::string &room_id, const Room &room_info, ErrorCodes &error) {
    return false;
}

bool PostgreDBWrapper::add_post(const std::string &post_id, const Post &post_info, ErrorCodes &error) {
    return false;
}

bool PostgreDBWrapper::add_user_to_room(const std::string &room_id, const std::string &user_id, ErrorCodes &error) {
    return false;
}

bool PostgreDBWrapper::add_session(const std::string &session_id, const Session &session_info, ErrorCodes &error) {
    return false;
}

bool PostgreDBWrapper::remove_user(const std::string &user_id, ErrorCodes &error) {
    return false;
}

bool PostgreDBWrapper::remove_room(const std::string &room_id, ErrorCodes &error) {
    return false;
}

bool PostgreDBWrapper::remove_post(const std::string &post_id, ErrorCodes &error) {
    return false;
}

bool
PostgreDBWrapper::remove_user_from_room(const std::string &room_id, const std::string &user_id, ErrorCodes &error) {
    return false;
}

bool PostgreDBWrapper::remove_session(const std::string &session_id, ErrorCodes &error) {
    return false;
}

DBUser PostgreDBWrapper::get_user_info(const std::string &user_id, ErrorCodes &error) const {
    return DBUser();
}

DBRoom PostgreDBWrapper::get_room_info(const std::string &room_id, ErrorCodes &error) const {
    return DBRoom();
}

DBPost PostgreDBWrapper::get_post_info(const std::string &post_id, ErrorCodes &error) const {
    return DBPost();
}

DBSession PostgreDBWrapper::get_session_info(const std::string &session_id, ErrorCodes &error) const {
    return DBSession();
}

bool PostgreDBWrapper::edit_user(const User &user_info, ErrorCodes &error) {
    return false;
}

bool PostgreDBWrapper::edit_room(const Room &room_info, ErrorCodes &error) {
    return false;
}

bool PostgreDBWrapper::edit_post(const Post &post_info, ErrorCodes &error) {
    return false;
}
