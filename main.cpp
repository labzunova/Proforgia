#include <iostream>
#include "database/include/Utils/DBEntities.h"
#include "database/include/Wrappers/StorageWrapperRealisations/AmazonS3StorageWrapper.h"

int main()
{
    ErrorCodes error;
//    AmazonS3StorageWrapper storage;
//    std::cout << storage.get_file_link("posts/2/2J9hyP65z8", error);

//    std::cout << DBPost::add(DBPost::Post(1, 1, "testpost13", "aaaaaa"), error) << " ";
//    std::cout << DBUser::add(DBUser::User("eeee", "eeeee", "xxx"), error) << " ";
//    std::cout << DBSession::add(DBSession::Session("ewrerewrwerreer", 1), error) << " ";
//    std::cout << DBSession::remove("ewrerewrwerreer", error);

    // DBPost::add_file_to_db("catty.jpg", "posts/4/KJHKJHjhjh6b7", 4, DBPost::FileType::IMAGE, error);

//    auto files = DBPost::get(4, error)->get_attachments(error);
//    files.value()[1].print();

    auto post = DBPost::get(3, error);
    post->print();
    post->update_tags({"матан", "амбразура", "тесты"}, error);

    return 0;
}

