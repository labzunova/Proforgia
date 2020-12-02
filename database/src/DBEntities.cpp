#include "../include/Utils/DBEntities.h"
#include "../include/DataManager.h"


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

DBEntity::DBEntity(std::string &_id) : db_manager(DataManager::getInstance()), id(_id) {}
