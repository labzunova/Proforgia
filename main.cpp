#include <iostream>
#include "database/include/Utils/DBEntities.h"
#include "database/include/Wrappers/StorageWrapperRealisations/AmazonS3StorageWrapper.h"

int main()
{
      ErrorCodes error;
//    AmazonS3StorageWrapper storage;
//    std::cout << storage.get_file_upload_link(120, error).value().first << std::endl;
//    std::cout << storage.get_file_link("test7.jpg", error);

//    std::cout << DBPost::add(DBPost::Post(1, 1, "testpost13", "aaaaaa"), error) << " ";
//    std::cout << DBUser::add(DBUser::User("eeee", "eeeee", "xxx"), error) << " ";
//    std::cout << DBSession::add(DBSession::Session("ewrerewrwerreer", 1), error) << " ";
//    std::cout << DBSession::remove("ewrerewrwerreer", error);

    // DBPost::add_file_to_db("catty.jpg", "posts/4/KJHKJHjhjh6b7", 4, DBPost::FileType::IMAGE, error);

//    auto files = DBPost::get(4, error)->get_attachments(error);
//    files.value()[1].print();

//    auto post = DBPost::get(3, error);
//    post->print();
//    post->update_tags({"матан", "амбразура", "тесты"}, error);

    // DBPost::add(DBPost::Post(1, "test null room_id", ""), error);
    auto post = DBPost::get(7, error);
    post->print();
    post->room_id = 0;
    auto res = post->update(error);
    post = DBPost::get(7, error);
    if (!res) std::cout << "not res" << std::endl;
    post->print();

    return 0;
}

