#include <string>
#include <vector>
#include "../Utils/DBEntities.h"
#include "../Utils/ErrorCodes.h"

using std::string;
using std::shared_ptr;

class DBWrapper {
public:
	DBWrapper() = default;
	virtual ~DBWrapper() = default;

	DBWrapper( const DBWrapper& ) = delete;
	DBWrapper& operator=( const DBWrapper& ) = delete;

protected:
	// для добавления расположения файла в Storage в таблицу files в БД
//	virtual bool add_file_record(
//		const std::string& file_id,
//		const std::string& filename,
//		const std::string& file_storage_ref,
//		const std::string& post_id,
//		ErrorCodes &error) = 0;

public:
    virtual bool add_user( const DBUser::User& user_info, ErrorCodes &error ) = 0;
	virtual bool add_room( const DBRoom::Room& room_info, ErrorCodes &error ) = 0;
//	virtual bool add_post( const std::string& post_id, const DBPost::Post& post_info, ErrorCodes &error ) = 0; // room_id and user_id inside Post
	virtual bool add_user_to_room( const int& room_id, const int& user_id, Rights user_rights, ErrorCodes &error ) = 0;
//	virtual bool add_session( const std::string& session_id, const DBSession::Session& session_info, ErrorCodes &error ) = 0;
//
	virtual bool remove_user( const int& user_id, ErrorCodes &error ) = 0;
	virtual bool remove_room( const int& room_id, ErrorCodes &error ) = 0;
//	virtual bool remove_post( const std::string& post_id, ErrorCodes &error ) = 0;
	virtual bool remove_user_from_room( const int& room_id, const int& user_id, ErrorCodes &error ) = 0;
//	virtual bool remove_session( const std::string& session_id, ErrorCodes &error ) = 0;

    virtual shared_ptr<DBUser> get_user_info( const int& user_id, ErrorCodes &error ) const = 0;
    virtual shared_ptr<DBUser> get_user_info( const string& nickname, ErrorCodes &error ) const = 0;
    virtual std::optional< vector<pair<DBRoom, Rights>> > get_user_rooms( const int& user_id, ErrorCodes &error ) const = 0;
	virtual shared_ptr<DBRoom> get_room_info( const int& room_id, ErrorCodes &error ) const = 0;
    virtual std::optional< vector<pair<DBUser, Rights>> > get_room_users( const int& room_id, ErrorCodes &error ) const = 0;
    virtual std::optional< vector<DBPost> > get_room_posts( const int& room_id, ErrorCodes &error ) const = 0;
    virtual std::optional< vector<DBTag> > get_room_tags( const int& room_id, ErrorCodes &error ) const = 0;
//	virtual DBPost get_post_info( const std::string& post_id, ErrorCodes &error ) const = 0;
//	virtual DBSession get_session_info( const std::string& session_id, ErrorCodes &error ) const = 0;
//
	virtual bool edit_user( const int& id, const DBUser::User& user_info, ErrorCodes &error ) = 0;
	virtual bool edit_room( const int& id, const DBRoom::Room& room_info, ErrorCodes &error ) = 0;
//	virtual bool edit_post( const DBPost::Post& post_info, ErrorCodes &error ) = 0;
};
