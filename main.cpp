#include <iostream>

#include "database/include/Utils/DBEntities.h"

#include "database/include/Wrappers/StorageWrapperRealisations/AmazonS3StorageWrapper.h"


int main()
{
    AmazonS3StorageWrapper storageWrapper;
    ErrorCodes error;

    storageWrapper.remove_file_from_storage("Test Folder/", error);
    return 0;
}