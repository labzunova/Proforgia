#include "../DBWrapper.h"

#include <memory>

extern "C"
{
    #include <libpq-fe.h>
}

// TODO: рассмотреть вариант заводить PGconn только при создании PostgreDBWrapper, чекать что он рабочий при каждом вызове
//  и переподключаться лениво, если с ним что то будет не так

class PostgreDBWrapper : public DBWrapper {
public:
	PostgreDBWrapper();
	~PostgreDBWrapper() override = default;

	PostgreDBWrapper( const PostgreDBWrapper& ) = delete;
	PostgreDBWrapper& operator=( const PostgreDBWrapper& ) = delete;

public:
	bool add_user( const DBUser::User& user_info, ErrorCodes &error ) override;
	bool add_room( const DBRoom::Room& room_info, ErrorCodes &error ) override;
	bool add_post( const DBPost::Post& post_info, ErrorCodes &error ) override;
    bool add_file(const string &filename, int post_id, ErrorCodes &error) override;
    bool add_user_to_room( const int& room_id, const int& user_id, Rights user_rights, ErrorCodes &error ) override;
    bool add_tags_to_post( std::vector<std::string>& _tags, const int& post_id, const int& room_id, ErrorCodes &error) override;
    bool add_session( const DBSession::Session& session_info, ErrorCodes &error ) override;

	bool remove_user( const int& user_id, ErrorCodes &error ) override;
	bool remove_room( const int& room_id, ErrorCodes &error ) override;
	bool remove_post( const int& post_id, ErrorCodes &error ) override;
	bool remove_user_from_room( const int& room_id, const int& user_id, ErrorCodes &error ) override;
	bool remove_session( const int& session_id, ErrorCodes &error ) override;

    shared_ptr<DBUser> get_user_info( const int& user_id, ErrorCodes &error ) const override;
    shared_ptr<DBUser> get_user_info( const string& nickname, ErrorCodes &error ) const override;
    std::optional< vector<pair<DBRoom, Rights>> > get_user_rooms( const int& user_id, ErrorCodes &error ) const override;
	shared_ptr<DBRoom> get_room_info( const int& room_id, ErrorCodes &error ) const override;
    std::optional< vector<pair<DBUser, Rights>> > get_room_users( const int& room_id, ErrorCodes &error ) const override;
    std::optional< vector<DBPost> > get_room_posts( const int& room_id, ErrorCodes &error ) const override;
    std::optional< vector<DBTag> > get_room_tags( const int& room_id, ErrorCodes &error ) const override;
    shared_ptr<DBPost> get_post_info( const int& post_id, ErrorCodes &error ) const override;
    std::optional< vector<int> > get_posts_by_tags(vector<string>& _tags, int room_id, ErrorCodes &error) const override;
    std::optional< vector<int> > get_post_tags_ids(int post_id, ErrorCodes &error) const override;
    shared_ptr<DBTag> get_tag_info( const int& tag_id, ErrorCodes &error ) const override;
    std::optional< std::vector<std::string> > get_post_attachments(int post_id, ErrorCodes &error) const override;
    shared_ptr<DBSession> get_session_info( const int& session_id, ErrorCodes &error ) const override;

	bool edit_user( const int& id, const DBUser::User& user_info, ErrorCodes &error ) override;
	bool edit_room( const int& id, const DBRoom::Room& room_info, ErrorCodes &error ) override;
	bool edit_post( const int& id, const DBPost::Post& post_info, ErrorCodes &error ) override;

private:
    shared_ptr<PGconn> get_connection() const;

    std::string host;
    std::string port;
    std::string db_name;
    std::string db_user;
    std::string db_user_password;
};