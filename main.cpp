#include <iostream>
#include "database/include/Utils/DBEntities.h"

using std::cout;
using std::endl;

#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/local_time/local_time.hpp"

using namespace boost::gregorian;
using namespace boost::local_time;
using namespace boost::posix_time;

local_date_time parse_timestamp_to_local_date_time(string str) {
    ptime pt(boost::posix_time::time_from_string(str));
    string timezone_str;
    for (int i = 2; i > 0; i--)
        timezone_str.push_back(str[str.size() - i]);
    int hours_cnt = std::stoi(timezone_str);

    ptime pt1;
    if (str[str.size()-3] == '+') pt1 = pt - hours(hours_cnt);
    else if (str[str.size()-3] == '-') pt1 = pt + hours(hours_cnt);
    else assert(false);

    timezone_str.insert(0, 1, str[str.size()-3]);

    time_zone_ptr zone(
            new posix_time_zone("MST" + timezone_str));
    local_date_time az(pt1, zone);
    return az;
}

int main()
{

    time_duration const_expire_time = hours(72) + seconds(10);

    // ptime current_time(second_clock::universal_time()); // UTC time

    local_date_time session_create_time(parse_timestamp_to_local_date_time("2020-12-08 22:39:52.074377+03"));

    // cout << current_time << endl;
    cout << session_create_time << endl;

    auto session_expire_time = session_create_time + const_expire_time;
    cout << session_expire_time << endl;

    time_zone_ptr zone(
            new posix_time_zone("MST+03")
    );
    local_date_time current_time = local_sec_clock::local_time(zone);

    cout << current_time << endl;

    if (current_time > session_expire_time) cout << "session expired << endl";
    else cout << "session valid";




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


    auto posts = DBPost::get({"tag1", "mathmathics", "physicsSuck"}, 2, error);
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
    }
    for (int i = 0; i < posts->size(); i++) {
        posts.value()[i].print();
        std::cout << std::endl;
    }
*/


    return 0;
}

