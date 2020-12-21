#include <iostream>
#include "database/include/Utils/DBEntities.h"
#include "database/include/Wrappers/StorageWrapperRealisations/AmazonS3StorageWrapper.h"

int main()
{
    ErrorCodes error;
//    AmazonS3StorageWrapper storage;
//    std::cout << storage.get_file_link("posts/2/2J9hyP65z8", error);

    std::cout << DBPost::add(DBPost::Post(1, 1, "testpost13", "aaaaaa"), error) << " ";
    std::cout << DBUser::add(DBUser::User("eeee", "eeeee", "xxx"), error) << " ";
    std::cout << DBSession::add(DBSession::Session("ewrerewrwerreer", 1), error) << " ";

    return 0;
}

