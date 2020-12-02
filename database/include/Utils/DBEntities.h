// TODO: убрать пустые контрукторы-заглушки как только в них не будет надобности (напишу реализацию DBWrapper)

#ifndef PROFORGIA_DBENTITIES_H
#define PROFORGIA_DBENTITIES_H

#include <string>
#include <vector>
#include <unordered_map>
#include "Rights.h"
#include "ErrorCodes.h"


class DataManager;

struct DBEntity {
	DBEntity(std::string& _id);

	DataManager& db_manager;

	std::string id;
	// boost::date date_of_creation;

	virtual bool update(ErrorCodes &error) = 0; // аналог save() в API UML
};


class DBRoom;

struct DBUser : public DBEntity {
	struct User {
		User( std::string& _nick_name, std::string& _email) :
			nick_name(_nick_name), 
			email(_email) {}

		std::string nick_name;
		std::string email;
	};


	DBUser(std::string &id, std::string &_nick_name, std::string &_email) :
            DBEntity(id), nick_name(_nick_name), email(_email) {

	}

	std::string nick_name;
	std::string email;

    // TODO: email, nickname should be unique to allow this get methods
	static DBUser get(std::string& _id, ErrorCodes &error); // by id or email or nickname

	static std::string add(User _user, ErrorCodes &error); // return id in DB on success, а при неудаче, вернет строку специального вида
	static bool remove(std::string& id, ErrorCodes &error);
	bool update(ErrorCodes &error) override;

	// методы получения связанных полей 
	std::unordered_map<DBRoom, Rights> get_rooms(ErrorCodes &error);
};

class DBTag : public DBEntity {
private:
	size_t use_count; // счетчик количества упоминаний тэга для более эффективной сортировки тэгов по популярности


public:
	std::string name;
};

class DBPost;

struct DBRoom : public DBEntity {
	struct Room {
		Room( std::string& _room_name, std::string& _description ) : 
		room_name(_room_name),
		description(_description) {}

		std::string room_name;
		std::string description;
	};

	DBRoom(std::string &id, std::string &_room_name, std::string &_description) :
            DBEntity(id), room_name(_room_name), description(_description) {}

	std::string room_name;
	std::string description;

	static DBRoom get(std::string& _id, ErrorCodes &error);
	static std::string add(Room _room, ErrorCodes &error); // return id in DB on success, а при неудаче, вернет строку специального вида
	static bool remove(std::string& id, ErrorCodes &error);

	static bool add_user(const std::string& room_id, const std::string& user_id, ErrorCodes &error);
	static bool remove_user(const std::string& room_id, const std::string& user_id, ErrorCodes &error);
	static bool add_discipline(const std::string& discipline_name, const std::string& room_id, const std::string& user_id, ErrorCodes &error);
	static bool add_category(const std::string& category_name, const std::string& discipline_name, const std::string& room_id, const std::string& user_id, ErrorCodes &error);

	bool update(ErrorCodes &error) override;

	// методы получения связанных полей 
	std::unordered_map<DBUser, Rights> get_users(ErrorCodes &error);
	std::vector<DBPost> get_posts(ErrorCodes &error);
	std::vector<DBTag> get_tags(ErrorCodes &error); // возвращает тэги, принадлежащие комнате, отсортированные по популярности (мб сделать выбор сортировки по дате или популярности)
};


struct DBPost : public DBEntity {
	// class for representation file in filesystem on server
	class FileFS {
		FileFS(const std::string& storage_filename);
		/*
		: path(_path) {
			filename = path.takeOnlyFilename
			auto path_to_file_in_storage = "root/path/to/storage/folder/" + this->id + "/" + storage_filename;
			ErrorCodes error;
			path = db_manager.get_file(storage_filename, path_to_file_in_storage, error);
			if (path == ERROR_STRING) {
				assert(false);
			}
		}
		*/

		~FileFS();
		/*
		{
			ErrorCodes error;
			if (!db_manager.clean_file(filename, path, error)) {
				assert(false);
			}
		}
		 */

        DataManager& db_manager;

		std::string filename;
		std::string path;
	};

	struct Post {
		Post( 
			std::string& _room_id, 
			std::string& _user_id, 
			std::string& _discipline, 
			std::string& _category, 
			std::string& _text,
			std::vector<std::string>& _attachments ) : 
				room_id(_room_id), 
				user_id(_user_id), 
				discipline(_discipline), 
				category(_category), 
				text(_text),
				attachments(_attachments)
		{}

		std::string room_id; 
		std::string user_id; // post author
		std::string discipline;
		std::string category;
		std::string text;
		std::vector<std::string> attachments; // list of files to add to the post in DB
	};

	DBPost(std::string &id, std::string &_room_id, std::string &_user_id, std::string &_title, std::string &_text) :
            DBEntity(id), room_id(_room_id), user_id(_user_id), title(_title), text(_text)
	{}

	std::string room_id; 
	std::string user_id; // post author

	std::string title;
	std::string text;

	static DBPost get(std::string& _id, ErrorCodes &error);
	static std::string add(Post _post, ErrorCodes &error); // return id in DB on success, а при неудаче, вернет строку специального вида
	static bool remove(std::string& id, ErrorCodes &error);
	bool update(ErrorCodes &error) override;

	static std::vector<DBPost> get(std::vector<std::string>& _tags, ErrorCodes &error);
	static std::vector<DBTag> get_associated_tags(std::vector<std::string>& _tags, ErrorCodes &error); // в порядке убывания упоминаний в других постах

	// методы получения связанных полей 
	DBRoom get_room(ErrorCodes &error);
	DBUser get_author(ErrorCodes &error);
	std::vector<DBTag> get_tags(ErrorCodes &error);
	/* 
	Если API будет нужно работать с vector<FileFS> вне стэка, в котором был вызыван метод get_attachments,
	то можно как вариант сделать модификацию метода, который будет отдавать ссылку на вектор, 
	выделенный в динамической памяти
	*/
	std::vector<FileFS> get_attachments(ErrorCodes &error); // list of storage locations of files, that is attached to post
};

struct DBSession : public DBEntity {
	struct Session {
	    Session( std::string& _user_id ) : user_id(_user_id) {}

	    std::string user_id;
	};

	DBSession(std::string &id, std::string &_user_id) : DBEntity(id), user_id(_user_id) {}

	std::string user_id;

	static DBSession get(std::string& _id, ErrorCodes &error);
	static std::string add(Session _session, ErrorCodes &error); // return id in DB on success, а при неудаче, вернет строку специального вида
	static bool remove(std::string& id, ErrorCodes &error);
	bool update(ErrorCodes &error) override;

	// методы получения связанных полей 
	DBUser get_user(ErrorCodes &error);
};

#endif // PROFORGIA_DBENTITIES_H