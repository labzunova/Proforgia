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

std::optional< vector<pair<DBRoom, Rights>> > DBUser::get_rooms(ErrorCodes &error) {
    return DataManager::getInstance().get_user_rooms(id, error);
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

shared_ptr<DBRoom> DBRoom::get(int _id, ErrorCodes &error) {
    return DataManager::getInstance().get_room_info(_id, error);
}

bool DBRoom::add(DBRoom::Room _room, ErrorCodes &error) {
    return DataManager::getInstance().add_room(_room, error);
}

bool DBRoom::remove(int id, ErrorCodes &error) {
    return DataManager::getInstance().remove_room(id, error);
}

bool DBRoom::add_user(const string &room_id, const string &user_id, ErrorCodes &error) {

}

bool DBRoom::remove_user(const string &room_id, const string &user_id, ErrorCodes &error) {

}

bool DBRoom::add_category(const string &category_name, const string &discipline_name, const string &room_id,
                          const string &user_id, ErrorCodes &error) {

}

bool
DBRoom::add_discipline(const string &discipline_name, const string &room_id, const string &user_id, ErrorCodes &error) {

}

bool DBRoom::update(ErrorCodes &error) {
    return DataManager::getInstance().edit_room(id, Room(room_name, description), error);
}

std::optional< vector<pair<DBUser, Rights>> > DBRoom::get_users(ErrorCodes &error) {

}

std::vector<DBPost> DBRoom::get_posts(ErrorCodes &error) {

}

std::vector<DBTag> DBRoom::get_tags(ErrorCodes &error) {

}
