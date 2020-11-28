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

#define DEFAULT_BUCKET "my-test-bucket-proforgia"

bool PutObject(const Aws::String& bucketName,
               const Aws::String& objectName,
               const Aws::String& filename,
               const Aws::String& region
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

        std::cout << "Added object '" << objectName << "' to bucket '"
                  << bucketName << "'.";
        return true;
    }
    else
    {
        std::cout << "Error: PutObject: " <<
                  outcome.GetError().GetMessage() << std::endl;

        return false;
    }
}

AmazonS3StorageWrapper::AmazonS3StorageWrapper() : bucket_name(DEFAULT_BUCKET) {}

bool AmazonS3StorageWrapper::add_file_to_storage(const std::string &filename, const std::string &location,
                                                         ErrorCodes &error) const {
    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {
        const Aws::String bucket_name = (Aws::String) this->bucket_name; // "my-test-bucket-proforgia"
        const Aws::String path_to_file = (Aws::String) location; // "/Users/Ivan/Desktop/my-test-file.sample"
        const Aws::String region = "eu-central-1";

        if (!PutObject(bucket_name, path_to_file, (Aws::String) filename, region)) {
            return false;
        }

    }
    Aws::ShutdownAPI(options);
    return true;
}

bool AmazonS3StorageWrapper::remove_file_from_storage(const std::string &filename, const std::string &remote_location,
                                                      ErrorCodes &error) const {
    return false;
}

#endif // PROFORGIA_AMAZONS3STORAGEWRAPPER_H