#include "../include/Utils/DBEntities.h"
#include "../include/DataManager.h"


DBUser DBUser::get(int& _id, ErrorCodes &error) {

}

DBUser DBUser::get(std::string &_nickname, ErrorCodes &error) {

}

std::string DBUser::add(DBUser::User _user, ErrorCodes &error) {

}

bool DBUser::remove(std::string &id, ErrorCodes &error) {

}

bool DBUser::update(ErrorCodes &error) {

}

std::unordered_map<DBRoom, Rights> DBUser::get_rooms(ErrorCodes &error) {

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

DBEntity::DBEntity(int&_id) : db_manager(DataManager::getInstance()), id(_id) {}
