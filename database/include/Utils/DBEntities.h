// TODO: убрать пустые контрукторы-заглушки как только в них не будет надобности (напишу реализацию DBWrapper)

#ifndef PROFORGIA_DBENTITIES_H
#define PROFORGIA_DBENTITIES_H

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include "Rights.h"
#include "ErrorCodes.h"
#include "boost/date_time/gregorian/gregorian.hpp"

using namespace boost::gregorian;
using std::string;
using std::shared_ptr;

/*
 ЗАДАЧИ ПО САМОЙ БАЗЕ ДАННЫХ:
 TODO: поле password у юзер должно хранить хэш (скорее всего это будет число, уточнить у сережи)
 TODO: сессия должна хранить строковый идентификатор сессии (скорее всего строка фикс. размера, уточнить)
 TODO: сделать имеил уникальным
 */


// TODO: ДОБАВИТЬ ENTITY DBFILE
// TODO: ДОБАВИТЬ ДАТЫ почти ко всем энтити!!!!
// TODO: еще раз подумать об архитектуре ошибок

// при неудаче методов, возвращающих bool, вернется false
// при неудаче get-методов, возвращающих умный указатель на какое-либо DBEntity, вернется nullptr
// соответственно, если метод завершился неудачно, смотрим ErrorCodes &error на тип ошибки и обрабатываем

struct DBEntity {
	virtual bool update(ErrorCodes &error) = 0; // аналог save() в API UML

    int get_id() const;

protected:
    int id;
    DBEntity(int& _id);
};


class DBRoom;

struct DBUser : public DBEntity {
	struct User {
		User( string _nick_name, string _email, string _password) :
			nick_name(_nick_name), 
			email(_email),
			password(_password) {}

		std::string nick_name;
		std::string email;
		std::string password;
	};

    DBUser(int &id, std::string &_nick_name, std::string& _date, std::string &_email, std::string& _password) :
            DBEntity(id), nick_name(_nick_name), register_date(from_simple_string(_date)), email(_email), password(_password) {

    }

	static shared_ptr<DBUser> get(int _id, ErrorCodes &error);
    // TODO: email should be unique to allow get method work with email, make email unique
	static shared_ptr<DBUser> get(std::string _nickname, ErrorCodes &error);

	static bool add(User _user, ErrorCodes &error);
	static bool remove(int id, ErrorCodes &error);
	bool update(ErrorCodes &error) override;

	// методы получения связанных полей 
	std::unordered_map<DBRoom, Rights> get_rooms(ErrorCodes &error);


	void print() {
	    std::cout << nick_name << " info:" << std::endl;
	    std::cout << "id: " << this->id << std::endl;
	    std::cout << "date: " << this->register_date << std::endl;
	    std::cout << "email: " << this->email << std::endl;
	}

    const string &getPassword() const;

    std::string nick_name;
    std::string email;
    date register_date;
private:
    std::string password;
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

	DBRoom(int &id, std::string &_room_name, std::string &_description) :
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
	struct Post {
		Post( 
			std::string& _room_id, 
			std::string& _user_id, 
			std::string& _title,
			std::string& _text,
			std::vector<std::string>& _attachments ) : 
				room_id(_room_id), 
				user_id(_user_id),
				title(_title),
				text(_text),
				attachments(_attachments)
		{}

		std::string room_id; 
		std::string user_id; // post author

        std::string title;
		std::string text;
		std::vector<std::string> attachments; // list of files to add to the post in DB
	};

	DBPost(int& id, std::string &_room_id, std::string &_user_id, std::string &_title, std::string &_text) :
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

	// методы получения связанных полей 
	DBRoom get_room(ErrorCodes &error);
	DBUser get_author(ErrorCodes &error);
	std::vector<DBTag> get_tags(ErrorCodes &error);

	std::vector<std::string> get_attachments(ErrorCodes &error); // list of links to storage locations of files
};

struct DBSession : public DBEntity {
	struct Session {
	    Session( std::string& _user_id ) : user_id(_user_id) {}

	    std::string user_id;
	};

	DBSession(int &id, std::string &_user_id) : DBEntity(id), user_id(_user_id) {}

	std::string user_id;

	static DBSession get(std::string& _id, ErrorCodes &error);
	static std::string add(Session _session, ErrorCodes &error); // return id in DB on success, а при неудаче, вернет строку специального вида
	static bool remove(std::string& id, ErrorCodes &error);
	bool update(ErrorCodes &error) override;

	// методы получения связанных полей 
	DBUser get_user(ErrorCodes &error);
};

#endif // PROFORGIA_DBENTITIES_H