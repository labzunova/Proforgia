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

    auto user = DBUser::get("gfdg", error);
    if (user) {
        user->print();
    } else {
        // handle
        switch(error) {
            case ErrorCodes::DB_ENTITY_NOT_FOUND:
                std::cout << "entity not found" << std::endl;
                break;
            default:
                std::cout << "other error" << std::endl;
        }
    }


    return 0;
}