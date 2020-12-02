#include "../StorageWrapper.h"

class AmazonS3StorageWrapper : public StorageWrapper {
public:
	AmazonS3StorageWrapper();
	~AmazonS3StorageWrapper() override = default;

	AmazonS3StorageWrapper( const AmazonS3StorageWrapper& ) = delete;
	AmazonS3StorageWrapper& operator=( const AmazonS3StorageWrapper& ) = delete;

public:
    /*
     * USING SAMPLE
    AmazonS3StorageWrapper storageWrapper;
    ErrorCodes error;
    if (!storageWrapper.add_file_to_storage("my-file-name-in-storage", "path/to/my/file", error)) {
        switch (error) {
            case ErrorCodes::UNKNOWN_STORAGE_ERROR:
                std::cout << "handled" << std::endl;
                break;
        }
    }
    */
	bool add_file_to_storage( const std::string& filename, const std::string& location, ErrorCodes &error ) const override;

    bool remove_file_from_storage( const std::string& filename, const std::string& remote_location /* ? */, ErrorCodes &error ) const override;

    std::string get_file( const std::string& filename, const std::string& location_on_server, ErrorCodes &error ) const override;

    virtual bool clean_file( const std::string& filename, const std::string& location_on_server, ErrorCodes &error ) const override;

private:
    const std::string bucket_name;
    const std::string region;
};



