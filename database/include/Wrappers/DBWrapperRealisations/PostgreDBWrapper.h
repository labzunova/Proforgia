#include "../DBWrapper.h"

class PostgreDBWrapper : public DBWrapper {
public:
	PostgreDBWrapper() = default;
	~PostgreDBWrapper() override = default;

	PostgreDBWrapper( const PostgreDBWrapper& ) = delete;
	PostgreDBWrapper& operator=( const PostgreDBWrapper& ) = delete;

protected:
	bool add_file_record( 
		const std::string& file_id, 
		const std::string& filename, 
		const std::string& file_storage_ref, 
		const std::string& post_id,
		ErrorCodes &error ) override;
public:
	bool add_user( const std::string& user_id, const User& user_info, ErrorCodes &error ) override;
	bool add_room( const std::string& room_id, const Room& room_info, ErrorCodes &error ) override;
	bool add_post( const std::string& post_id, const Post& post_info, ErrorCodes &error ) override;
	bool add_user_to_room( const std::string& room_id, const std::string& user_id, ErrorCodes &error ) override;
	bool add_session( const std::string& session_id, const Session& session_info, ErrorCodes &error ) override;

	bool remove_user( const std::string& user_id, ErrorCodes &error ) override;
	bool remove_room( const std::string& room_id, ErrorCodes &error ) override;
	bool remove_post( const std::string& post_id, ErrorCodes &error ) override;
	bool remove_user_from_room( const std::string& room_id, const std::string& user_id, ErrorCodes &error ) override;
	bool remove_session( const std::string& session_id, ErrorCodes &error ) override;

	DBUser get_user_info( const std::string& user_id, ErrorCodes &error ) const override;
	DBRoom get_room_info( const std::string& room_id, ErrorCodes &error ) const override;
	DBPost get_post_info( const std::string& post_id, ErrorCodes &error ) const override;
	DBSession get_session_info( const std::string& session_id, ErrorCodes &error ) const override;

	bool edit_user( const User& user_info, ErrorCodes &error ) override;
	bool edit_room( const Room& room_info, ErrorCodes &error ) override;
	bool edit_post( const Post& post_info, ErrorCodes &error ) override;
};