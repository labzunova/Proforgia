#include "DBEntites.h"

// TODO: дописать псевдокод и сделать рабочий метод
std::vector<FileFS> DBPost::get_attachments(ErrorCodes &error) {
	auto storage_filenames = db_manager.get_post_attachments_storagenames(this->id, error);
	if (false /* failure */) {
		// handle
	}

	std::vector<FileFS> files;
	files.capacity = storage_filenames.size();
	for (filename : storage_filenames) {
		files.emplace(FileFS(filename))
	}

	return files;

}