#include <string>
#include <vector>
#include "../Utils/InputEntities.h"
#include "../Utils/DBEntities.h"
#include "../Utils/ErrorCodes.h"

// TODO: если оберкти будут на стороне сережи, то убрать DBentities а внутренние методы структур вынести как отдельные методы DBWrapper

class DBWrapper {
public:
	DBWrapper() = default;
	virtual ~DBWrapper() = default;

	DBWrapper( const DBWrapper& ) = delete;
	DBWrapper& operator=( const DBWrapper& ) = delete;

protected:
	// для добавления расположения файла в Storage в таблицу files в БД
	virtual bool add_file_record( 
		const std::string& file_id, 
		const std::string& filename, 
		const std::string& file_storage_ref, 
		const std::string& post_id,
		ErrorCodes &error) = 0;

public:
	virtual bool add_user( const std::string& user_id, const User& user_info, ErrorCodes &error ) = 0;
	virtual bool add_room( const std::string& room_id, const Room& room_info, ErrorCodes &error ) = 0;
	virtual bool add_post( const std::string& post_id, const Post& post_info, ErrorCodes &error ) = 0; // room_id and user_id inside Post
	virtual bool add_user_to_room( const std::string& room_id, const std::string& user_id, ErrorCodes &error ) = 0;
	virtual bool add_session( const std::string& session_id, const Session& session_info, ErrorCodes &error ) = 0;

	virtual bool remove_user( const std::string& user_id, ErrorCodes &error ) = 0;
	virtual bool remove_room( const std::string& room_id, ErrorCodes &error ) = 0;
	virtual bool remove_post( const std::string& post_id, ErrorCodes &error ) = 0;
	virtual bool remove_user_from_room( const std::string& room_id, const std::string& user_id, ErrorCodes &error ) = 0;
	virtual bool remove_session( const std::string& session_id, ErrorCodes &error ) = 0;

	virtual DBUser get_user_info( const std::string& user_id, ErrorCodes &error ) const = 0;
	virtual DBRoom get_room_info( const std::string& room_id, ErrorCodes &error ) const = 0;
	virtual DBPost get_post_info( const std::string& post_id, ErrorCodes &error ) const = 0;
	virtual DBSession get_session_info( const std::string& session_id, ErrorCodes &error ) const = 0;

	virtual bool edit_user( const User& user_info, ErrorCodes &error ) = 0;
	virtual bool edit_room( const Room& room_info, ErrorCodes &error ) = 0;
	virtual bool edit_post( const Post& post_info, ErrorCodes &error ) = 0;
};
