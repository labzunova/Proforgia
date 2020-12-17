#ifndef PROFORGIA_DBENTITIES_H
#define PROFORGIA_DBENTITIES_H

#include <string>
#include <utility>
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

 */

// при неудаче методов, возвращающих bool, вернется false
// при неудаче get-методов, возвращающих умный указатель на какое-либо DBEntity, вернется nullptr
// если возвращаемое значение метода обернуто в std::optional, то при неудаче оно сконвертируется в false
// соответственно, если метод завершился неудачно, смотрим ErrorCodes &error на тип ошибки и обрабатываем

struct DBEntity {
	virtual bool update(ErrorCodes &error) = 0; // аналог save() в API UML

    [[nodiscard]] int get_id() const;

protected:
    int id;
    explicit DBEntity(int& _id);
};


class DBRoom;

struct DBUser : public DBEntity {
	struct User {
        User( string _nick_name, string _email, string _password) :
			nick_name(std::move(_nick_name)),
			email(std::move(_email)),
			password(std::move(_password)) {}

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
    // std::optional конвертируется в bool и используется для определения, успешно ли завершилась функция
	std::optional< vector<pair<DBRoom, Rights>> > get_rooms(ErrorCodes &error);


	void print() {
	    std::cout << nick_name << " info:" << std::endl;
	    std::cout << "id: " << this->id << std::endl;
	    std::cout << "date: " << this->register_date << std::endl;
	    std::cout << "email: " << this->email << std::endl;
	}

    [[nodiscard]] const string &getPassword() const;

    std::string nick_name;
    std::string email;
    date register_date;
private:
    std::string password;
};

class DBTag : public DBEntity {
public:
    DBTag(int &id, string name, int roomId);

    bool update(ErrorCodes &error) override; // поля тэга менять нельзя, всегда вернет false

    static shared_ptr<DBTag> get(int _id, ErrorCodes &error);

    struct Tag {
        Tag(string name, int roomId);

        string name;
        int room_id;
    };

    void print() {
        std::cout << "Tag info:" << std::endl;
        std::cout << "id: " << this->id << std::endl;
        std::cout << "name: " << this->name << std::endl;
        std::cout << "room id: " << this->room_id << std::endl;
    }

    const string &getName() const;

    int getRoomId() const;

private:
	// size_t use_count; // счетчик количества упоминаний тэга для более эффективной сортировки тэгов по популярности
	string name;
	int room_id;
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

const static string POSTS_TABLE_NAME = "posts";
struct DBPost : public DBEntity {
	struct Post {
        Post(int roomId, int userId, const string &title, const string &text);

		int room_id;
		int user_id; // post author

        string title;
		string text;
	};

	DBPost(int& id, int &_room_id, int &_user_id, std::string &_title, std::string &_text, local_date_time& _ldt) :
            DBEntity(id), room_id(_room_id), user_id(_user_id), title(_title), text(_text), publication_date(_ldt)
	{}

	std::string title;
	std::string text;

	static shared_ptr<DBPost> get(int _id, ErrorCodes &error);
	static bool add(const Post& _post, ErrorCodes &error);
	static bool remove(int id, ErrorCodes &error);
	bool update(ErrorCodes &error) override;

    static std::optional< vector<DBPost> > get(std::vector<std::string> _tags, int room_id, ErrorCodes &error);

    // TODO: !!! допродумать работу с файлами на клиенте
    // TODO: и дописать до рабочего состояния методы по работе с файлами поста с учетом работы формы
    static string get_upload_link(int post_id, ErrorCodes &error); // !!! чтобы отдать ссылку нужно знать название файла ИНАЧЕ название будет генерится автоматом
    static bool add_file_to_db(string filename, ErrorCodes &error); // filename - имя файла, с которым он загрузился в Хранилище
    static bool remove_file(string filename, ErrorCodes &error); // filename - имя файла, с которым он загрузился в Хранилище

    // !!! полностью заменяет текущие тэги этого поста на тэги в new_tags
    bool update_tags(vector<string> new_tags, ErrorCodes &error); // для добавления/обновления списка тэгов у поста

	// методы получения связанных полей 
    shared_ptr<DBRoom> get_room(ErrorCodes &error);
    shared_ptr<DBUser> get_author(ErrorCodes &error);
    std::optional< vector<DBTag> > get_tags(ErrorCodes &error);
    std::optional< vector<std::string> > get_attachments(ErrorCodes &error); // list of links to storage locations of files


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
    int room_id;
    int user_id; // post author
    local_date_time publication_date;
};

struct DBSession : public DBEntity {
	struct Session {
        Session(const string sessionId, int userId);

        string session_identificator;
	    int user_id;
	};

    DBSession(int &id, const local_date_time &creationDate, const string &sessionId, int userId);

	static shared_ptr<DBSession> get(int _id, ErrorCodes &error);
	static bool add(Session _session, ErrorCodes &error);
	static bool remove(int id, ErrorCodes &error);
	bool update(ErrorCodes &error) override; // поля сессии менять нельзя, всегда вернет false

	// методы получения связанных полей 
    shared_ptr<DBUser> get_user(ErrorCodes &error);

    // getters
    const local_date_time &getCreationDate() const;
    const string &getSessionIdentificator() const;
    int getUserId() const;
private:
    local_date_time creation_date;
    string session_identificator;
    int user_id;
};

#endif // PROFORGIA_DBENTITIES_H