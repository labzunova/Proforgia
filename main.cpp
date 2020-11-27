#include <iostream>

#include "database/include/DataManager.h"

#include <fstream>
#include <sys/stat.h>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/PutObjectRequest.h>

bool PutObject(const Aws::String& bucketName,
               const Aws::String& objectName,
               const Aws::String& region)
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
    request.SetKey("my-file-with-222another-key.txt");

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


int main()
{
    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {
        const Aws::String bucket_name = "my-test-bucket-proforgia";
        const Aws::String object_name = "/Users/Ivan/Desktop/my-test-file.sample";
        const Aws::String region = "eu-central-1";

        if (!PutObject(bucket_name, object_name, region)) {
            return 1;
        }

    }
    Aws::ShutdownAPI(options);
    std::cout << "end-of-main" << std::endl;
    return 0;
}