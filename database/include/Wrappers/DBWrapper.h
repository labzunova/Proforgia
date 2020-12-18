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

public:
    virtual bool add_user( const DBUser::User& user_info, ErrorCodes &error ) = 0;
	virtual bool add_room( const DBRoom::Room& room_info, ErrorCodes &error ) = 0;
	virtual bool add_post( const DBPost::Post& post_info, ErrorCodes &error ) = 0;
    virtual bool add_file(const string &client_name, const string &storage_name, int post_id, ErrorCodes &error) = 0;
	virtual bool add_user_to_room( const int& room_id, const int& user_id, Rights user_rights, ErrorCodes &error ) = 0;
	virtual bool add_tags_to_post( std::vector<std::string>& _tags, const int& post_id, const int& room_id, ErrorCodes &error ) = 0;
	virtual bool add_session( const DBSession::Session& session_info, ErrorCodes &error ) = 0;

	virtual bool remove_user( const int& user_id, ErrorCodes &error ) = 0;
	virtual bool remove_room( const int& room_id, ErrorCodes &error ) = 0;
	virtual bool remove_post( const int& post_id, ErrorCodes &error ) = 0;
	virtual bool remove_user_from_room( const int& room_id, const int& user_id, ErrorCodes &error ) = 0;
	virtual bool remove_session( const int& session_id, ErrorCodes &error ) = 0;
    virtual bool remove_file(const std::string& client_name, const std::string& storage_filename, ErrorCodes &error) = 0;

    virtual shared_ptr<DBUser> get_user_info( const int& user_id, ErrorCodes &error ) const = 0;
    virtual shared_ptr<DBUser> get_user_info( const string& nickname, ErrorCodes &error ) const = 0;
    virtual std::optional< vector<pair<DBRoom, Rights>> > get_user_rooms( const int& user_id, ErrorCodes &error ) const = 0;
	virtual shared_ptr<DBRoom> get_room_info( const int& room_id, ErrorCodes &error ) const = 0;
    virtual std::optional< vector<pair<DBUser, Rights>> > get_room_users( const int& room_id, ErrorCodes &error ) const = 0;
    virtual std::optional< vector<DBPost> > get_room_posts( const int& room_id, ErrorCodes &error ) const = 0;
    virtual std::optional< vector<DBTag> > get_room_tags( const int& room_id, ErrorCodes &error ) const = 0;
	virtual shared_ptr<DBPost> get_post_info( const int& post_id, ErrorCodes &error ) const = 0;
	virtual std::optional< vector<int> > get_posts_by_tags(std::vector<std::string>& _tags, int room_id, ErrorCodes &error) const = 0;
    virtual std::optional< vector<int> > get_post_tags_ids(int post_id, ErrorCodes &error) const = 0;
    virtual std::optional< std::vector<std::string> > get_post_attachments(int post_id, ErrorCodes &error) const = 0;
    virtual shared_ptr<DBTag> get_tag_info( const int& tag_id, ErrorCodes &error ) const = 0;
	virtual shared_ptr<DBSession> get_session_info( const int& session_id, ErrorCodes &error ) const = 0;

	virtual bool edit_user( const int& id, const DBUser::User& user_info, ErrorCodes &error ) = 0;
	virtual bool edit_room( const int& id, const DBRoom::Room& room_info, ErrorCodes &error ) = 0;
	virtual bool edit_post( const int& id, const DBPost::Post& post_info, ErrorCodes &error ) = 0;
};
