#include <iostream>
#include "server/Server.h"
#include "src/Worker.cpp"

#include "database/include/Utils/DBEntities.h"
using std::cout;
using std::endl;

typedef std::map<std::string, std::string> Context;
class MockHandler {
public:
    explicit MockHandler(Context&) {};
    std::string get_response() {
        return "< HTTP/1.1 200 OK\n"
               "< Date: Tue, 08 Dec 2020 10:22:27 GMT\n"
               "< Server: WSGIServer/0.2 CPython/3.6.9\n"
               "< Content-Type: text/html; charset=utf-8\n"
               "< X-Frame-Options: DENY\n"
               "< Content-Length: 193\n"
               "< Vary: Cookie\n"
               "< X-Content-Type-Options: nosniff\n"
               "< Referrer-Policy: same-origin\n"
               "< \n"
               "\n"
               "\n"
               "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\" \"http://www.w3.org/TR/html4/strict.dtd\">\n"
               "<html>\n"
               " <head>\n"
               "  <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n"
               "  <title>Пример веб-страницы</title>\n"
               " </head>\n"
               " <body>\n"
               "  <h1>Заголовок</h1>\n"
               "  <!-- Комментарий -->\n"
               "  <p>Первый абзац.</p>\n"
               "  <p>Второй абзац.</p>\n"
               " </body>\n"
               "</html>";

    }
};

int main( int argc, char* argv[] ) {
    //  if ( argc != 2 )
    //      std::cout << "enter an address and port";
    //  else
    {
        std::shared_ptr<Connection_queue> queue = std::make_shared<Connection_queue>();
        Server server("127.0.0.1", "5000", *queue);
        // Server server( argv[0], argv[1], queue ); // TODO: думаю так очередь не передают (мб сделать синглтон?...)
        Work<Connection_queue, MockHandler> work;
        work.start_work(queue);
        server.start_server();
    }




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
 */

    return 0;
}

