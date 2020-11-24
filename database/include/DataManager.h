#include <memory> // https://habr.com/ru/post/140222/

class DataManager {
private:
	std::shared_ptr<DBWrapper> database;
	std::shared_ptr<StorageWrapper> storage;

public:
	// use Mayer's singleton realisation to be thread safe: 
	// https://habr.com/ru/post/147373/
	static DataManager& getInstance(); 

	DataManager( const DataManager& ) = delete;
	DataManager& operator=( const DataManager& ) = delete;

private:
	DataManager();
	~DataManager();

public:
	// методы add возвращающие строку, возвращают присовенное записи в БД id (логика генерации id тоже будет в данном классе), 
	// планируется, что это будет глобальный id объекта в приложении

	// при неудаче методов, возвращающих строку, вернется строка специального вида
	// при неудаче методов, возвращающих bool, вернется false
	std::string& add_user( const User& user_info, ErrorCodes &error ) const;
	std::string& add_room( const Room& room_info, ErrorCodes &error ) const;
	std::string& add_post( const Post& post_info, ErrorCodes &error ) const;
	std::string& add_session( const Session& session_info, ErrorCodes &error ) const;
	bool add_user_to_room( const std::string& room_id, const std::string& user_id, ErrorCodes &error ) const;
	bool add_discipline( const std::string& discipline_name, const std::string& room_id, const std::string& user_id ) const;
	bool add_category(const std::string& category_name, const std::string& discipline_name, const std::string& room_id, const std::string& user_id ) const;

	bool remove_user( const std::string& user_id, ErrorCodes &error ) const;
	bool remove_room( const std::string& room_id, ErrorCodes &error ) const;
	bool remove_post( const std::string& post_id, ErrorCodes &error ) const;
	bool remove_user_from_room( const std::string& room_id, const std::string& user_id, ErrorCodes &error ) const;
	bool remove_session( const std::string& session_id, ErrorCodes &error );

	User& get_user_info( const std::string& user_id ) const;
	Room& get_room_info( const std::string& room_id ) const;
	Post& get_post_info( const std::string& post_id ) const;
	Session& get_session_info( const std::string& session_id ) const;

	bool edit_user( const std::string& user_id, const User& user_info ) const;
	bool edit_room( const std::string& room_id, const Room& room_info ) const;
	bool edit_post( const std::string& post_id, const Post& post_info ) const;
}

// мб в Wrapper сделать отдельные методы для получения списка юзеров/ комнат у юзера а тут уже собирать из них структуру

