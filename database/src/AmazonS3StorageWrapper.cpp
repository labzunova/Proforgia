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
#include <aws/s3/model/DeleteObjectRequest.h>

#define DEFAULT_BUCKET "my-test-bucket-proforgia"
#define DEFAULT_REGION "eu-central-1"
#define DEFAULT_TO_CLIENT_PATH "/Users/Ivan/Proforgia-files/files-to-client/"
#define DEFAULT_FROM_CLIENT_PATH "/Users/Ivan/Proforgia-files/files-from-client/"
#define POSTS_FILES_FOLDER_NAME "posts/"

// TODO: add boost log

bool put_object(const Aws::String& bucketName,
                const Aws::String& objectName,
                const Aws::String& filename,
                const Aws::String& region,
                ErrorCodes &error
);
std::string get_object(const Aws::String& objectKey, const Aws::String& fromBucket, const std::string& path_to_file, ErrorCodes &error);
std::string get_upload_link(const Aws::String& region, const Aws::String& bucket);

AmazonS3StorageWrapper::AmazonS3StorageWrapper() :
    bucket_name(DEFAULT_BUCKET),
    region(DEFAULT_REGION),
    files_to_client_path(DEFAULT_TO_CLIENT_PATH),
    files_from_client_path(DEFAULT_FROM_CLIENT_PATH) {}

// TODO: implement folder for every entity with files (probably for every post)
// TODO: test method with private release bucket
std::string AmazonS3StorageWrapper::get_file_link(const std::string &filename, ErrorCodes &error) const {
    Aws::SDKOptions options;
    Aws::InitAPI(options);
    Aws::String url;
    {
        Aws::Client::ClientConfiguration config;

        if (!region.empty())
        {
            config.region = region;
        }

        Aws::S3::S3Client s3_client(config);
        // TODO: consider POST http method
        url = s3_client.GeneratePresignedUrl((Aws::String)this->bucket_name, (Aws::String)filename, Aws::Http::HttpMethod::HTTP_GET, 2000);
        std::cout << "Get file URL for " << filename << ":" << std::endl << url << std::endl;
    }

    Aws::ShutdownAPI(options);
    return (std::string)url; // !
}

// TODO: implement folder for every entity with files (probably for every post)
// TODO: test method with private release bucket
std::string AmazonS3StorageWrapper::get_file_upload_link(const std::string &filename, ErrorCodes &error) const {
    Aws::SDKOptions options;
    Aws::InitAPI(options);
    Aws::String url;
    {
        Aws::Client::ClientConfiguration config;

        if (!region.empty())
        {
            config.region = region;
        }

        Aws::S3::S3Client s3_client(config);
        // TODO: consider POST http method
        url = s3_client.GeneratePresignedUrl((Aws::String)this->bucket_name, (Aws::String)filename, Aws::Http::HttpMethod::HTTP_PUT, 2000);
        std::cout << "Upload URL for " << filename << ":" << std::endl << url << std::endl;
    }

    Aws::ShutdownAPI(options);
    return (std::string) url;
}

// pre-declaration
bool DeleteObject(const Aws::String& objectKey, const Aws::String& fromBucket, const Aws::String& region);

bool AmazonS3StorageWrapper::remove_file_from_storage(const std::string &filename, ErrorCodes &error) const {

    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {
        if (DeleteObject((Aws::String) filename, (Aws::String) this->bucket_name, (Aws::String) this->region))
        {
            std::cout << "Deleted object " << filename << " from " << this->bucket_name << "." << std::endl;
        } else {
            error = ErrorCodes::UNKNOWN_STORAGE_ERROR;
            ShutdownAPI(options);
            return false;
        }
    }
    ShutdownAPI(options);
    return true;
}


bool DeleteObject(const Aws::String& objectKey, const Aws::String& fromBucket, const Aws::String& region)
{
    Aws::S3::S3Client s3_client;
    Aws::S3::Model::DeleteObjectRequest request;

    request.WithKey(objectKey)
            .WithBucket(fromBucket);

    Aws::S3::Model::DeleteObjectOutcome outcome =
            s3_client.DeleteObject(request);

    if (!outcome.IsSuccess())
    {
        auto err = outcome.GetError();
        std::cout << "Error: DeleteObject: " <<
                  err.GetExceptionName() << ": " << err.GetMessage() << std::endl;

        return false;
    }
    else
    {
        return true;
    }
}


// get_upload_link((Aws::String)this->region, (Aws::String)this->bucket_name);
std::string get_upload_link(const Aws::String& region, const Aws::String& bucket) {
    Aws::Client::ClientConfiguration config;

    if (!region.empty())
    {
        config.region = region;
    }

    Aws::S3::S3Client s3_client(config);
    Aws::String url = s3_client.GeneratePresignedUrl(bucket, "smilee.jpg", Aws::Http::HttpMethod::HTTP_PUT, 2000);
    std::cout << url << std::endl;
    return (std::string) url;
}



/*
     * USING SAMPLE
    AmazonS3StorageWrapper storageWrapper;
    ErrorCodes error;
    if (!storageWrapper.add_file_to_storage("my-file-name", error)) {
        switch (error) {
            case ErrorCodes::UNKNOWN_STORAGE_ERROR:
                std::cout << "handled" << std::endl;
                break;
        }
    }
    */
bool add_file_to_storage(const std::string &filename, ErrorCodes &error) {
    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {
        const Aws::String bucket_name = (Aws::String)DEFAULT_BUCKET;
        const Aws::String region = (Aws::String)DEFAULT_REGION;
        const Aws::String path_to_file = (Aws::String) (DEFAULT_FROM_CLIENT_PATH + filename);
        const Aws::String file_name = (Aws::String) filename;

        if (!put_object(bucket_name, path_to_file, file_name, region, error)) {
            return false;
        }

    }

    Aws::ShutdownAPI(options);
    return true;
}


/*
     * USING SAMPLE
    AmazonS3StorageWrapper storageWrapper;
    ErrorCodes error;
    if (storageWrapper.get_file_beginning("myfile.pdf", error) == ERROR_STRING) {
        switch (error) {
            case ErrorCodes::UNKNOWN_STORAGE_ERROR:
                std::cout << "handled" << std::endl;
                break;
        }
    }
     */
std::string get_file_beginning( const std::string& filename, ErrorCodes &error ) {
    Aws::SDKOptions options;
    Aws::InitAPI(options);

    const Aws::String bucket_name = (Aws::String) DEFAULT_BUCKET;
    const Aws::String file_name = (Aws::String) filename;

    std::string result = get_object(file_name, bucket_name, DEFAULT_TO_CLIENT_PATH + filename, error);
    if (result == ERROR_STRING) {
        // maybe do smth to handle at this point or remove if it''ll only be handled on the upper level
        return ERROR_STRING;
    }

    Aws::ShutdownAPI(options);
    return result;
}

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

std::string get_object(const Aws::String& objectKey, const Aws::String& fromBucket, const std::string& path_to_file, ErrorCodes &error)
{
    Aws::S3::S3Client s3_client;
    Aws::S3::Model::GetObjectRequest object_request;
    object_request.SetBucket(fromBucket);
    object_request.SetKey(objectKey);

    Aws::S3::Model::GetObjectOutcome get_object_outcome =
            s3_client.GetObject(object_request);

    if (get_object_outcome.IsSuccess())
    {
        auto& retrieved_file = get_object_outcome.GetResultWithOwnership().GetBody();
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


#endif // PROFORGIA_AMAZONS3STORAGEWRAPPER_H