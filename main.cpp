#include <iostream>

#include "database/include/Utils/DBEntities.h"

#include "database/include/Wrappers/StorageWrapperRealisations/AmazonS3StorageWrapper.h"
#include "database/include/Wrappers/DBWrapperRealisations/PostgreDBWrapper.h"



int main()
{
    ErrorCodes error;
//    PostgreDBWrapper db;
//    // AmazonS3StorageWrapper st;
//    ErrorCodes error;
//
//    auto user = db.get_user_info(3, error);
//    user->print();

    auto user = DBUser::get(3, error);
    user->print();

    return 0;
}