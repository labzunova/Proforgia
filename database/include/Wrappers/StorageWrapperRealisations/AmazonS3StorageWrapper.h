#include "../StorageWrapper.h"

class AmazonS3StorageWrapper : public StorageWrapper {
public:
	AmazonS3StorageWrapper() = default;
	~AmazonS3StorageWrapper() override = default;

	AmazonS3StorageWrapper( const AmazonS3StorageWrapper& ) = delete;
	AmazonS3StorageWrapper& operator=( const AmazonS3StorageWrapper& ) = delete;

public:
	std::string add_file_to_storage( const std::string& filename, const std::string& location /* ? */, ErrorCodes &error ) const override; // return location in storage
	bool remove_file_from_storage( const std::string& filename, const std::string& remote_location /* ? */, ErrorCodes &error ) const override;
};