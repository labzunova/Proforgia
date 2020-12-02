//
// Created by Иван on 24.11.2020.
//
#ifndef PROFORGIA_AMAZONS3STORAGEWRAPPER_H
#define PROFORGIA_AMAZONS3STORAGEWRAPPER_H

#include "../include/Wrappers/StorageWrapperRealisations/AmazonS3StorageWrapper.h"

#include <fstream>
#include <sys/stat.h>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/PutObjectRequest.h>
#include <aws/s3/model/GetObjectRequest.h>

#define DEFAULT_BUCKET "my-test-bucket-proforgia"
#define DEFAULT_REGION "eu-central-1"

AmazonS3StorageWrapper::AmazonS3StorageWrapper() : bucket_name(DEFAULT_BUCKET), region(DEFAULT_REGION) {}

bool put_object(const Aws::String& bucketName,
                const Aws::String& objectName,
                const Aws::String& filename,
                const Aws::String& region,
                ErrorCodes &error
               )
{
    // Verify that the file exists.
    struct stat buffer;

    if (stat(objectName.c_str(), &buffer) == -1)
    {
        std::cout << "Error: PutObject: File '" <<
                  objectName << "' does not exist." << std::endl;

        return false;
    }

    Aws::Client::ClientConfiguration config;

    if (!region.empty())
    {
        config.region = region;
    }

    Aws::S3::S3Client s3_client(config);

    Aws::S3::Model::PutObjectRequest request;
    request.SetBucket(bucketName);
    request.SetKey(filename);

    std::shared_ptr<Aws::IOStream> input_data =
            Aws::MakeShared<Aws::FStream>("SampleAllocationTag",
                                          objectName.c_str(),
                                          std::ios_base::in | std::ios_base::binary);

    request.SetBody(input_data);

    Aws::S3::Model::PutObjectOutcome outcome =
            s3_client.PutObject(request);

    if (outcome.IsSuccess()) {

        // std::cout << "Added object '" << objectName << "' to bucket '" << bucketName << "'.";
        return true;
    }
    else
    {
        // std::cout << "Error message: PutObject: " << outcome.GetError().GetMessage() << std::endl;
        error = ErrorCodes::UNKNOWN_STORAGE_ERROR;
        return false;
    }
}

bool AmazonS3StorageWrapper::add_file_to_storage(const std::string &filename, const std::string &location,
                                                         ErrorCodes &error) const {
    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {
        const Aws::String bucket_name = (Aws::String) this->bucket_name;
        const Aws::String region = (Aws::String) this->region;
        const Aws::String path_to_file = (Aws::String) location;
        const Aws::String file_name = (Aws::String) filename;

        if (!put_object(bucket_name, path_to_file, file_name, region, error)) {
            return false;
        }

    }
    Aws::ShutdownAPI(options);
    return true;
}


std::string get_object(const Aws::String& objectKey, const Aws::String& fromBucket, ErrorCodes &error)
{
    Aws::S3::S3Client s3_client;
    Aws::S3::Model::GetObjectRequest object_request;
    object_request.SetBucket(fromBucket);
    object_request.SetKey(objectKey);

    Aws::S3::Model::GetObjectOutcome get_object_outcome =
            s3_client.GetObject(object_request);

    if (get_object_outcome.IsSuccess())
    {
        // TODO: put retrieved file on server filesystem
        auto& retrieved_file = get_object_outcome.GetResultWithOwnership().
                GetBody();

        // Print a beginning portion of the text file.
        std::cout << "Beginning of file contents:\n";
        char file_data[255] = { 0 };
        retrieved_file.getline(file_data, 254);
        std::cout << file_data << std::endl;

        return "path/to/file/on/server";
    }
    else
    {
        auto err = get_object_outcome.GetError();
        std::cout << "Error: GetObject: " <<
                  err.GetExceptionName() << ": " << err.GetMessage() << std::endl;

        error = ErrorCodes::UNKNOWN_STORAGE_ERROR;
        return ERROR_STRING;
    }
}

std::string AmazonS3StorageWrapper::get_file( const std::string& filename, ErrorCodes &error ) const {
    Aws::SDKOptions options;
    Aws::InitAPI(options);

    const Aws::String bucket_name = (Aws::String) this->bucket_name;
    const Aws::String file_name = (Aws::String) filename;

    std::string result = get_object(file_name, bucket_name, error);
    if (result == ERROR_STRING) {
        // maybe do smth to handle at this point or remove if it''ll only be handled on the upper level
        return ERROR_STRING;
    }

    Aws::ShutdownAPI(options);
    return result;
}

bool AmazonS3StorageWrapper::remove_file_from_storage(const std::string &filename, const std::string &remote_location,
                                                      ErrorCodes &error) const {
    return false;
}

bool AmazonS3StorageWrapper::clean_file(const std::string &filename, const std::string &location_on_server,
                                        ErrorCodes &error) const {
    return false;
}

#endif // PROFORGIA_AMAZONS3STORAGEWRAPPER_H