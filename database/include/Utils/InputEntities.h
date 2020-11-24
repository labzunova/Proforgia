// Вспомогательные структуры. Испуользуются при добавлении новых сущностей в БД

struct User {
	User( std::string& _nick_name, std::string& _email = nullptr ) : 
		nick_name(_nick_name), 
		email(_email) {}

	std::string nick_name;
	std::string email;
}

struct Room {
	Room( std::string& _room_name, std::string& _description ) : 
	room_name(_room_name),
	description(_description) {}

	std::string room_name;
	std::string description;
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
	std::vector<std::string> attachments; // list of files to add to the post in DB
}

struct Session {
	Session( std::string& _user_id ) : user_id(_user_id) {}

	std::string user_id;
	// ???
}