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
	int add_user( const DBUser::User& user_info, ErrorCodes &error ) const;
	int add_room( const DBRoom::Room& room_info, ErrorCodes &error ) const;
	int add_post( const DBPost::Post& post_info, ErrorCodes &error ) const;
    bool add_file(const string &client_name, const string &storage_name, int post_id, DBPost::FileType fileType,
                  ErrorCodes &error) const;
	int add_session( const DBSession::Session& session_info, ErrorCodes &error ) const;
	bool add_user_to_room( const int& room_id, const int& user_id, Rights user_rights, ErrorCodes &error ) const;
    bool add_tags_to_post( std::vector<std::string>& _tags, const int& post_id, const int& room_id, ErrorCodes &error ) const;

	bool remove_user( const int& user_id, ErrorCodes &error ) const;
	bool remove_room( const int& room_id, ErrorCodes &error ) const;
	bool remove_post( const int& post_id, ErrorCodes &error ) const;
	bool remove_user_from_room( const int& room_id, const int& user_id, ErrorCodes &error ) const;
	bool remove_session( const int& session_id, ErrorCodes &error );

	bool edit_user( const int& user_id, const DBUser::User& user, ErrorCodes &error ) const;
	bool edit_room( const int& room_id, const DBRoom::Room& room, ErrorCodes &error ) const;
	bool edit_post( const int& post_id, const DBPost::Post& post, ErrorCodes &error ) const;

	shared_ptr<DBUser> get_user_info( const int& user_id, ErrorCodes &error ) const;
	shared_ptr<DBUser> get_user_info( const string& nickname, ErrorCodes &error ) const;
    std::optional< vector<pair<DBRoom, Rights>> > get_user_rooms( const int& user_id, ErrorCodes &error ) const;
    shared_ptr<DBRoom> get_room_info( const int& room_id, ErrorCodes &error ) const;
    std::optional< vector<pair<DBUser, Rights>> > get_room_users( const int& room_id, ErrorCodes &error ) const;
    std::optional< vector<DBPost> > get_room_posts( const int& room_id, ErrorCodes &error ) const;
    std::optional< vector<DBTag> > get_room_tags( const int& room_id, ErrorCodes &error ) const;
    shared_ptr<DBPost> get_post_info( const int& post_id, ErrorCodes &error ) const;
    std::optional< vector<DBPost> > get_posts_by_tags(vector<string>& _tags, int room_id, ErrorCodes &error) const;
    std::optional< std::vector<DBTag> > get_post_tags(int post_id, ErrorCodes &error) const;
    std::optional< std::vector<DBPost::FileData> > get_post_attachments(int post_id, ErrorCodes &error) const;
    shared_ptr<DBTag> get_tag_info( const int& tag_id, ErrorCodes &error ) const;
    shared_ptr<DBSession> get_session_info( const int& session_id, ErrorCodes &error ) const;
    shared_ptr<DBSession> get_session_info( const string& session_identificator, ErrorCodes &error ) const;

	std::string get_file_link( const std::string& filename, ErrorCodes &error ) const;
    std::optional< std::pair<std::string, std::string> > get_file_upload_link(int post_id, ErrorCodes &error ) const;
	bool remove_file_from_storage( const std::string& filename, ErrorCodes &error ) const;
	bool remove_file_from_database(const std::string& client_name, const std::string& storage_filename, ErrorCodes &error);
};
