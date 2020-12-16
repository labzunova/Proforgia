#include <iostream>
#include "database/include/Utils/DBEntities.h"

using std::cout;
using std::endl;

int main()
{

    ErrorCodes error;
    // примеры использования методов интерфейса
/*
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

    auto user = DBUser::get(1, error);
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

    auto rooms = user->get_rooms(error);
    if(!rooms) {
        switch(error) {
            case ErrorCodes::DB_CONNECTION_ERROR:
                std::cout << "connection error" << std::endl;
                break;
            case ErrorCodes::UNKNOWN_DB_ERROR:
                std::cout << "unknown error" << std::endl;
                break;
            default:
                assert(false);
        }
    } else {
        for (int i = 0; i < rooms->size(); i++) {
            rooms.value()[i].first.print();
        }
    }

    auto room = DBRoom::get(11, error);
    if (room) {
        room->print();
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

    bool res = DBRoom::add(DBRoom::Room("myroomname3"), error);
    if (!res) {
        switch(error) {
            case ErrorCodes::DB_CONNECTION_ERROR:
                std::cout << "connection error" << std::endl;
                break;
            default:
                std::cout << "other error" << std::endl;
        }
    }

    bool res = DBRoom::remove(7, error);
    if (!res) {
        switch(error) {
            case ErrorCodes::DB_CONNECTION_ERROR:
                std::cout << "connection error" << std::endl;
                break;
            default:
                std::cout << "other error" << std::endl;
        }
    }



    room->room_name = "newName";
    room->description = "newDescription";
    bool res = room->update(error);
    if (!res) {
        assert(false);
    }



    bool res = DBRoom::add_user(1, 1, Rights::MEMBER, error);
    if (!res) {
        switch(error) {
            case ErrorCodes::DB_CONNECTION_ERROR:
                std::cout << "connection error" << std::endl;
                break;
            default:
                std::cout << "other error" << std::endl;
        }
    }

    res = DBRoom::remove_user(1, 1, error);
    if (!res) {
        switch(error) {
            case ErrorCodes::DB_CONNECTION_ERROR:
                std::cout << "connection error" << std::endl;
                break;
            default:
                std::cout << "other error" << std::endl;
        }
    }


    auto room = DBRoom::get(3, error);
    if (room) {
        room->print();
        std::cout << std::endl << std::endl;
        ErrorCodes error1;
        auto room_users = room->get_users(error1);
        if (room_users) {
            for (int i = 0; i < room_users->size(); i++) {
                room_users.value()[i].first.print();
                std::cout << std::endl;
            }
        } else assert(false);
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


    auto room = DBRoom::get(4, error);
    auto room_posts = room->get_posts(error);
    if (room_posts) {
        for (int i = 0; i < room_posts->size(); i++) {
            room_posts.value()[i].print();
            std::cout << std::endl;
        }
    } else assert(false);

    auto room_tags = room->get_tags(error);
    if (room_tags) {
        for (int i = 0; i < room_tags->size(); i++) {
            room_tags.value()[i].print();
            std::cout << std::endl;
        }
        if (room_tags->empty()) cout << "No tags";
    } else assert(false);


    bool res = DBPost::add(DBPost::Post(2, 1, "postAddedFromCode", "aaaaa"), error);
    if (!res) assert(false);

    res = DBPost::remove(8, error);
    if (!res) assert(false);

    auto post = DBPost::get(9, error);
    if (post) post->print();
    else assert(error == ErrorCodes::DB_ENTITY_NOT_FOUND);

    post->text = "updated text";
    post->update(error);

    auto posts = DBPost::get({"право", "физра", "матан"}, 1, error);
    if (!posts) {
        switch(error) {
            case DB_CONNECTION_ERROR:
                std::cout << "DB_CONNECTION_ERROR" << std::endl;
                break;
            case DB_ENTITY_NOT_FOUND:
                std::cout << "DB_ENTITY_NOT_FOUND" << std::endl;
                break;
            case UNKNOWN_DB_ERROR:
                std::cout << "UNKNOWN_DB_ERROR" << std::endl;
                break;
            default:
                std::cout << "????????" << std::endl;
                break;
        }
    } else {
        for (int i = 0; i < posts->size(); i++) {
            posts.value()[i].print();
            std::cout << std::endl;
        }
    }


    auto post = posts.value()[0];
    bool res = post.update_tags({ "матан", "физра", "право", "новыйЗавет" }, error);
    if (!res) {
        switch(error) {
            case DB_CONNECTION_ERROR:
                std::cout << "DB_CONNECTION_ERROR" << std::endl;
                break;
            case DB_ENTITY_NOT_FOUND:
                std::cout << "DB_ENTITY_NOT_FOUND" << std::endl;
                break;
            case UNKNOWN_DB_ERROR:
                std::cout << "UNKNOWN_DB_ERROR" << std::endl;
                break;
            default:
                std::cout << "????????" << std::endl;
                break;
        }
    }

    auto link = DBPost::get_upload_link(2, error);
    DBPost::remove_file("file-with-text.txt", error);

    auto tag = DBTag::get(2, error);
    if (!tag) assert(false);
    cout << tag->getName() << " ";
    cout << tag->getRoomId();


    auto post = DBPost::get(1, error);
    auto tags = post->get_tags(error);
    for (int i = 0; i < tags->size(); i++) {
        cout << tags.value()[i].getName() << " ";
    }
    if (tags->empty()) cout << "No tags";

    auto post = DBPost::get(2, error);
    auto attachments = post->get_attachments(error);
    for (int i = 0; i < attachments->size(); i++) {
        cout << attachments.value()[i] << " ";
    }
    */

    


    return 0;
}

