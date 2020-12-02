#include <iostream>

#include "database/include/Utils/DBEntities.h"

#include "database/include/Wrappers/StorageWrapperRealisations/AmazonS3StorageWrapper.h"




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