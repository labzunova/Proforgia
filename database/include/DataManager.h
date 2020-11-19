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

