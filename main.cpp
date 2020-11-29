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
    if (storageWrapper.get_file("my-file.txt", error) == ERROR_STRING) {
        switch (error) {
            case ErrorCodes::UNKNOWN_STORAGE_ERROR:
                std::cout << "handled" << std::endl;
                break;
        }
    }
    std::cout << "end-of-main" << std::endl;
    return 0;
}