#include <iostream>

#include "database/include/DataManager.h"

#include <fstream>
#include <sys/stat.h>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/PutObjectRequest.h>




int main()
{
    AmazonS3StorageWrapper storageWrapper;
    ErrorCodes error;
    storageWrapper.add_file_to_storage("my-file-throw-class", "/Users/Ivan/Desktop/my-test-file.sample", error);
    std::cout << "end-of-main" << std::endl;
    return 0;
}