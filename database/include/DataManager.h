#include <memory> // for std::shared_ptr https://habr.com/ru/post/140222/
#include "Wrappers/DBWrapperRealisations/PostgreDBWrapper.h"
#include "Wrappers/StorageWrapperRealisations/AmazonS3StorageWrapper.h"
#include "Utils/DBEntities.h"

using std::string;
using std::shared_ptr;

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
	~DataManager() = default;

public:
	bool add_user( const DBUser::User& user_info, ErrorCodes &error ) const;
	bool add_room( const DBRoom::Room& room_info, ErrorCodes &error ) const;
	bool add_post( const DBPost::Post& post_info, ErrorCodes &error ) const;
	std::string add_session( const DBSession::Session& session_info, ErrorCodes &error ) const;
	bool add_user_to_room( const int& room_id, const int& user_id, Rights user_rights, ErrorCodes &error ) const;

	bool remove_user( const int& user_id, ErrorCodes &error ) const;
	bool remove_room( const int& room_id, ErrorCodes &error ) const;
	bool remove_post( const int& post_id, ErrorCodes &error ) const;
	bool remove_user_from_room( const int& room_id, const int& user_id, ErrorCodes &error ) const;
	bool remove_session( const int& session_id, ErrorCodes &error );

	bool edit_user( const int& user_id, const DBUser::User& user, ErrorCodes &error ) const;
	bool edit_room( const int& room_id, const DBRoom::Room& room, ErrorCodes &error ) const;
	bool edit_post( const int& post_id, const DBPost::Post& post, ErrorCodes &error ) const;
	bool edit_session( const int& session_id, const DBSession& session, ErrorCodes &error ) const;

	shared_ptr<DBUser> get_user_info( const int& user_id, ErrorCodes &error ) const;
	shared_ptr<DBUser> get_user_info( const string& nickname, ErrorCodes &error ) const;
    std::optional< vector<pair<DBRoom, Rights>> > get_user_rooms( const int& user_id, ErrorCodes &error ) const;
    shared_ptr<DBRoom> get_room_info( const int& room_id, ErrorCodes &error ) const;
    std::optional< vector<pair<DBUser, Rights>> > get_room_users( const int& room_id, ErrorCodes &error ) const;
    std::optional< vector<DBPost> > get_room_posts( const int& room_id, ErrorCodes &error ) const;
    std::optional< vector<DBTag> > get_room_tags( const int& room_id, ErrorCodes &error ) const;
    shared_ptr<DBPost> get_post_info( const int& post_id, ErrorCodes &error ) const;
	DBSession get_session_info( const std::string& session_id, ErrorCodes &error ) const;

	std::vector<std::string> get_post_attachments_links( const std::string& post_id, ErrorCodes &error ) const;

	std::string get_file_link( const std::string& filename, ErrorCodes &error ) const;
	std::string get_file_upload_link( const std::string& filename, ErrorCodes &error ) const;
	bool remove_file_from_storage( const std::string& filename, const std::string& remote_location /* ? */, ErrorCodes &error ) const;
};

