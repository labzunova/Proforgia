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

    auto res = DBUser::add(DBUser::User("cool_nickname_2", "basket.ivan@mail.ru", "xxx"), error);
    if (!res) {
        switch(error) {
            case ErrorCodes::DB_CONNECTION_ERROR:
                std::cout << "connection error" << std::endl;
                break;
            default:
                std::cout << "other error" << std::endl;
        }
    }

    auto user = DBUser::get("cool_nickname_2", error);
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

    user->email = "dfgfdgdfgdfgdf";
    user->nick_name = "aaaaaaaa";
    res = user->update(error);
    if (!res) {
        switch(error) {
            case ErrorCodes::DB_CONNECTION_ERROR:
                std::cout << "connection error" << std::endl;
                break;
            default:
                std::cout << "other error" << std::endl;
        }
    }


    return 0;
}