#include "../include/Utils/DBEntities.h"
#include "../include/DataManager.h"


shared_ptr<DBUser> DBUser::get(int _id, ErrorCodes &error) {
    return DataManager::getInstance().get_user_info(_id, error);
}

shared_ptr<DBUser> DBUser::get(std::string _nickname, ErrorCodes &error) {
    return DataManager::getInstance().get_user_info(_nickname, error);
}

bool DBUser::add(DBUser::User _user, ErrorCodes &error) {
    return DataManager::getInstance().add_user(_user, error);
}

bool DBUser::remove(int id, ErrorCodes &error) {
    return DataManager::getInstance().remove_user(id, error);
}

bool DBUser::update(ErrorCodes &error) {
    return DataManager::getInstance().edit_user(id, User(nick_name, email, password), error);
}

std::unordered_map<DBRoom, Rights> DBUser::get_rooms(ErrorCodes &error) {

}

const string &DBUser::getPassword() const {
    return password;
}


// TODO: дописать псевдокод и сделать рабочий метод
std::vector<std::string> DBPost::get_attachments(ErrorCodes &error) {

}

std::vector<DBPost> DBPost::get(std::vector<std::string>& _tags, ErrorCodes &error) {
	// get all posts, that contain all tags in _tags
}

// Это не надо, сережа реализует у себя!
std::vector<DBTag> get_associated_tags(std::vector<std::string>& _tags, ErrorCodes &error) {
	// get all posts, that contain all tags in _tags
	// get all tags, from every post that was found
	// sort tags by popularity (via unordered map?)
	// return tags in sorted order
}

DBEntity::DBEntity(int& _id) : id(_id) {}

int DBEntity::get_id() const {
    return id;
}
