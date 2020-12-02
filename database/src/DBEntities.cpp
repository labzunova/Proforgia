#include "../include/Utils/DBEntities.h"
#include "../include/DataManager.h"


// TODO: дописать псевдокод и сделать рабочий метод
std::vector<DBPost::FileFS> DBPost::get_attachments(ErrorCodes &error) {
    /*
	auto storage_filenames = db_manager.get_post_attachments_storagenames(this->id, error);
	if ( failure ) {
		// handle
	}

	std::vector<FileFS> files;
	files.capacity = storage_filenames.size();
	for (filename : storage_filenames) {
		files.emplace(FileFS(filename))
	}

	return files;
    */
}

std::vector<DBPost> DBPost::get(std::vector<std::string>& _tags, ErrorCodes &error) {
	// get all posts, that contain all tags in _tags
}


std::vector<DBTag> DBPost::get_associated_tags(std::vector<std::string>& _tags, ErrorCodes &error) {
	// get all posts, that contain all tags in _tags
	// get all tags, from every post that was found
	// sort tags by popularity (via unordered map?)
	// return tags in sorted order
}

DBEntity::DBEntity(std::string &_id) : db_manager(DataManager::getInstance()), id(_id) {}
