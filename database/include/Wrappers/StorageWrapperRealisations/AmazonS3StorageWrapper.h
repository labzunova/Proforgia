#include "../StorageWrapper.h"

class AmazonS3StorageWrapper : public StorageWrapper {
public:
	AmazonS3StorageWrapper();
	~AmazonS3StorageWrapper() override = default;

	AmazonS3StorageWrapper( const AmazonS3StorageWrapper& ) = delete;
	AmazonS3StorageWrapper& operator=( const AmazonS3StorageWrapper& ) = delete;

public:
	bool add_file_to_storage( const std::string& filename, const std::string& location /* ? */, ErrorCodes &error ) const override; // return location in storage
	bool remove_file_from_storage( const std::string& filename, const std::string& remote_location /* ? */, ErrorCodes &error ) const override;

private:
    const std::string bucket_name;
};



/*
 TODO: aws-sdk folder ADDED IN .gitignore FOR NOW !!!

 Progress setting up s3:
 + aws sdk det up
 + aws credentials provided (throw aws configure in ~/.aws folder
 CURRENT: Using the AWS SDK for C++: https://docs.aws.amazon.com/sdk-for-cpp/v1/developer-guide/basic-use.html
*/