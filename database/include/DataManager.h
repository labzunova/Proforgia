// Status - структура, хранящая в себе виды ошибок

// TODO: обернуть в namespace
struct User;
struct Room;
enum Rights;
struct Post;
struct Session;

class DataManager {
private:
	DBWrapper* database;
	StorageWrapper* storage;

public:
	// should use mutex and be thread safe: 
	// https://refactoring.guru/ru/design-patterns/singleton/cpp/example#example-1
	static DataManager* getInstance(); 

	DataManager( const DataManager& ) = delete;
	DataManager& operator=( const DataManager& ) = delete;

private:
	static DataManager* instance;

	DataManager();
	~DataManager();

public:
	// методы add возвращаюobt строку, возвращают присовенное записи в БД id (логика генерации id тоже будет в данном классе), 
	// планируется, что это будет глобальный id объекта в приложении

	// при неудаче методов, возвращающих строку, вернется строка специального вида
	// при неудаче методов, возвращающих bool, вернется false
	std::string& add_user( const User& user_info, ErrorCodes &error );
	std::string& add_room( const Room& room_info, ErrorCodes &error );
	std::string& add_post( const Post& post_info, ErrorCodes &error );
	std::string& add_session( const Session& session_info, ErrorCodes &error );
	bool add_user_to_room( const std::string& room_id, const std::string& user_id, ErrorCodes &error );
	bool add_discipline( const std::string& discipline_name, const std::string& room_id, const std::string& user_id );
	bool add_category(const std::string& category_name, const std::string& discipline_name, const std::string& room_id, const std::string& user_id );

	bool remove_user( const std::string& user_id, ErrorCodes &error );
	bool remove_room( const std::string& room_id, ErrorCodes &error );
	bool remove_post( const std::string& post_id, ErrorCodes &error );
	bool remove_user_from_room( const std::string& room_id, const std::string& user_id, ErrorCodes &error );
	bool remove_session( const std::string& session_id, ErrorCodes &error );

	User& get_user_info( const std::string& user_id );
	Room& get_room_info( const std::string& room_id );
	Post& get_post_info( const std::string& post_id );
	Session& get_session_info( const std::string& session_id );

	bool edit_user( const std::string& user_id, const User& user_info );
	bool edit_room( const std::string& room_id, const Room& room_info );
	bool edit_post( const std::string& post_id, const Post& post_info );
}


// мб в Wrapper сделать отдельные методы для получения списка юзеров/ комнат у юзера а тут уже собирать из них структуру

struct User {
	User( std::string& _nick_name, std::vector<std::pair<std::string, Rights>>& _rooms, std::string& _email = nullptr ) : 
		nick_name(_nick_name), 
		email(_email),
		rooms(_rooms) {}

	std::string nick_name;
	std::string email;

	std::vector<std::pair<std::string, Rights>> rooms; // pair: room_id, rights

	// TODO: fill Users DB table and finish struct
}

struct Room {
	Room( std::string& _room_name, std::vector<std::pair<std::string, Rights>>& _users ) : 
	room_name(_room_name),
	users(_users) {}

	std::string room_name;
	// std::string description;

	std::vector<std::pair<std::string, Rights>> users; // pair: user_id, rights

	// TODO: consider adding list of posts id in (?)

	// TODO: fill Rooms DB table and finish struct
}

enum Rights {
	CREATOR,
	ADMIN,
	MEMBER
}

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

	// TODO: Post on add and Post on get methods will propably have different vector values (on get - file ids in BD)
	// solve this problem (maybe template class, or separate classes, or move it from class or smth different..)
	std::vector<std::string> attachments; // list of files, that is attached to post
}

struct Session {
	Session( std::string& _user_id ) : user_id(_user_id) {}

	std::string user_id;

	// TODO: fill Sessions DB table and finish struct
}