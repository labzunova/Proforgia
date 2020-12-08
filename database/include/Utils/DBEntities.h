#ifndef PROFORGIA_DBENTITIES_H
#define PROFORGIA_DBENTITIES_H

#include <string>
#include <vector>
#include <optional>
#include <iostream>
#include <unordered_map>

#include "Rights.h"
#include "ErrorCodes.h"

#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/local_time/local_time.hpp"

using namespace boost::gregorian;
using namespace boost::local_time;
using namespace boost::posix_time;

using std::string;
using std::shared_ptr;
using std::vector;
using std::pair;

/*
 ЗАДАЧИ ПО САМОЙ БАЗЕ ДАННЫХ:
 TODO: поле password у юзер должно хранить хэш (скорее всего это будет число, уточнить у сережи)
 TODO: сессия должна хранить строковый идентификатор сессии (скорее всего строка фикс. размера, уточнить)
 TODO: сделать имеил уникальным
 TODO: исправить typo room_desciption на room_description
 TODO: сделать поля user_id и room_id not null в таблице posts
 */


// TODO: ДОБАВИТЬ ENTITY DBFILE
// TODO: ДОБАВИТЬ ДАТЫ почти ко всем энтити!!!!


// при неудаче методов, возвращающих bool, вернется false
// при неудаче get-методов, возвращающих умный указатель на какое-либо DBEntity, вернется nullptr
// если возвращаемое значение метода обернуто в std::optional, то при неудаче оно сконвертируется в false
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

	// возвращает массив пар, пара - комната и права пользователя в этой комнате
	std::optional< vector<pair<DBRoom, Rights>> > get_rooms(ErrorCodes &error);


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
		Room( std::string _room_name, std::string _description = "" ) :
		room_name(_room_name),
		description(_description) {}

		std::string room_name;
		std::string description;
	};

	DBRoom(int &id, std::string &_room_name, std::string &_description, string& _create_date) :
            DBEntity(id), room_name(_room_name), description(_description), create_date(from_simple_string(_create_date)) {}

    ~DBRoom() = default;

    std::string room_name;
    std::string description;

	static shared_ptr<DBRoom> get(int _id, ErrorCodes &error);
	static bool add(Room _room, ErrorCodes &error);
	static bool remove(int id, ErrorCodes &error);

	static bool add_user(const int& room_id, const int& user_id, Rights user_rights, ErrorCodes &error);
	static bool remove_user(const int& room_id, const int& user_id, ErrorCodes &error);

	bool update(ErrorCodes &error) override;

	// методы получения связанных полей
    std::optional< vector<pair<DBUser, Rights>> > get_users(ErrorCodes &error);
    std::optional< std::vector<DBPost> > get_posts(ErrorCodes &error); // TODO: сортировка по дате
    std::optional< std::vector<DBTag> > get_tags(ErrorCodes &error); // TODO: сортировка по дате/популярности


    void print() {
        std::cout << "Room info:" << std::endl;
        std::cout << "id: " << this->id << std::endl;
        std::cout << "name: " << this->room_name << std::endl;
        std::cout << "description: " << this->description << std::endl;
        std::cout << "date: " << this->create_date << std::endl;
    }

private:
    date create_date;
};


struct DBPost : public DBEntity {
	struct Post {
		Post( 
			std::string& _room_id, 
			std::string& _user_id, 
			std::string& _title,
			std::string& _text,
            vector<string> _tags,
			std::vector<std::string>& _attachments ) :
				room_id(_room_id), 
				user_id(_user_id),
				title(_title),
				text(_text),
				tags(_tags),
				attachments(_attachments)
		{}

		std::string room_id; 
		std::string user_id; // post author

        std::string title;
		std::string text;
		vector<string> tags;
		std::vector<std::string> attachments; // list of files to add to the post in DB
	};

	DBPost(int& id, int &_room_id, int &_user_id, std::string &_title, std::string &_text, local_date_time& _ldt) :
            DBEntity(id), room_id(_room_id), user_id(_user_id), title(_title), text(_text), publication_date(_ldt)
	{}

	int room_id;
	int user_id; // post author

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

    void print() {
        std::cout << "Post info:" << std::endl;
        std::cout << "id: " << this->id << std::endl;
        std::cout << "room id: " << this->room_id << std::endl;
        std::cout << "user id: " << this->user_id << std::endl;
        std::cout << "publication date and time: " << this->publication_date << std::endl;
        std::cout << "title: " << this->title << std::endl;
        std::cout << "text: " << this->text << std::endl;
    }
private:
    local_date_time publication_date;
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