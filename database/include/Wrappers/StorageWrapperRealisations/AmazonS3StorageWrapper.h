#include "../StorageWrapper.h"

class AmazonS3StorageWrapper : public StorageWrapper {
public:
	AmazonS3StorageWrapper();
	~AmazonS3StorageWrapper() override = default;

	AmazonS3StorageWrapper( const AmazonS3StorageWrapper& ) = delete;
	AmazonS3StorageWrapper& operator=( const AmazonS3StorageWrapper& ) = delete;

public:
    std::string get_file_link( const std::string& filename, ErrorCodes &error ) const override;
    std::string get_file_upload_link( const std::string& filename, ErrorCodes &error ) const override;

    // true if file was deleted, or there was not such file to delete
    // able to remove folders
    bool remove_file_from_storage( const std::string& filename, ErrorCodes &error ) const override;

private:
    const std::string bucket_name;
    const std::string region;
    const std::string files_to_client_path;
    const std::string files_from_client_path;
};



