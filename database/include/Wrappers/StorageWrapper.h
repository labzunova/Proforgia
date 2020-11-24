class StorageWrapper {
public:
	DBWrapper() = default;
	virtual ~DBWrapper() {}

	DBWrapper( const DBWrapper& ) = delete;
	DBWrapper& operator=( const DBWrapper& ) = delete;

public:
	virtual std::string& add_file_to_storage( const std::string& filename, const std::string& location /* ? */, , ErrorCodes &error ) const = 0; // return location in storage
	virtual bool remove_file_from_storage( const std::string& filename, const std::string& remote_location /* ? */, ErrorCodes &error ) const = 0;
}