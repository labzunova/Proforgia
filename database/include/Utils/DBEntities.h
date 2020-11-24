/*
Идея:
сделать абстрактный класс сущности с методами типа add() all() remove() get() на подобии QuerySet в Django и наследоваться всеми сущностями от него
*/

// TODO: сделать public методы для возврата связных сущностей данной сущности (чтобы выполнять доп. работу только при необходимости)

struct DBUser {
	DBUser( std::string& _id, std::string& _nick_name, std::string& _email = nullptr ) : 
		id(_id),
		nick_name(_nick_name), 
		email(_email) {}

	std::string id;
	std::string nick_name;
	std::string email;

	// TODO: consider using map or unordered_map
	std::vector<std::pair<std::string, Rights>> get_rooms(); // return pair: room_id, rights
}

struct DBRoom {
	DBRoom( std::string& _id, std::string& _room_name, std::string& _description ) :
	id(_id), 
	room_name(_room_name),
	description(_description) {}

	std::string id;
	std::string room_name;
	std::string description;

	// TODO: consider using map or unordered_map
	std::vector<std::pair<std::string, Rights>> get_users(); // return pair: user_id, rights
	std::vector<std::string> get_posts_id(); // return pair: user_id, rights
}

struct DBPost {
	DBPost( 
		std::string& _id,
		std::string& _room_id, 
		std::string& _user_id, 
		std::string& _discipline, 
		std::string& _category, 
		std::string& _text,
		std::vector<std::string>& _attachments ) : 
			id(_id),
			room_id(_room_id), 
			user_id(_user_id), 
			discipline(_discipline), 
			category(_category), 
			text(_text),
			attachments(_attachments)
	{}

	std::string id;
	std::string room_id; 
	std::string user_id; // post author
	std::string discipline;
	std::string category;
	std::string text;

	std::vector<std::string> get_attachments(); // list of storage locations of files, that is attached to post
}

struct DBSession {
	DBSession( std::string& _id, std::string& _user_id ) : id(_id), user_id(_user_id) {}

	std::string id;
	std::string user_id;
}
