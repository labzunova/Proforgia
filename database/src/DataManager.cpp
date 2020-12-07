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




