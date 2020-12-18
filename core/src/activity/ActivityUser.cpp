//
// Created by sergei on 28.11.2020.
//

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

#include "ActivityUser.h"
#include <boost/log/trivial.hpp>
#include <openssl/sha.h>

string SHA(string data)
{
    typedef unsigned char byte;
    byte const* pb_data = (byte*) data.data();
    unsigned int data_len = data.size();

    byte ab_digest[SHA_DIGEST_LENGTH];
    SHA1(pb_data, data_len, ab_digest);

    return std::string((char*)ab_digest);
}

ActivityManager::Status ActivityUser::signUp(std::string& session) {
    if(!validate_signUp())
        return CLIENT_ERROR;

    std::string login = context_["login"];
    std::string email = context_["mail"];
    context_["password"] = "xxxx";
    BOOST_LOG_TRIVIAL(debug) << std::to_string(context_["password"].size());
//    std::string password = SHA(context_["password"]);
    std::string password = context_["password"]; // временное
    typename DBUser::User user(login, email, password);
    BOOST_LOG_TRIVIAL(debug) << password;

    ErrorCodes er;
    bool ex = DBUser::add(user, er); // TODO проверка на то прошло ли сохранение, вернуться когда будет бд

    assert(ex == true);

    int id = 0; /// временное решение

    session = create_session();
    save_session(id, session);
    return OK;
}

ActivityManager::Status ActivityUser::login(std::string& session) {
    if(!validate_signIn())
        return CLIENT_ERROR;

    std::string login = context_["login"];
    std::string password = SHA(context_["password"]);
    ErrorCodes er;
    auto user = DBUser::get(login, er); // TODO проверка на то пришел ли User
    if(user->password != password)
        return CLIENT_ERROR;

    //session = create_session(user.id);
    return OK;
}

ActivityUser::ActivityUser(ContextMap &context) : ActivityManager(context) {
}

bool ActivityUser::validate_signUp() {
    // TODO добавить еще разные проверки
    auto end = context_.end();
    if((context_.find("login") == end) ||
        (context_.find("password") == end) ||
        (context_.find("mail") == end))

        return false;

    return true;
}

// создание случайных байт для сессии
string ActivityUser::create_session() {
    const int size_session = 40;

    srand( time(0) );

    auto randchar = []() -> char
    {
        const char charset[] =
                "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str(size_session,0);
    std::generate_n( str.begin(), size_session, randchar );
    return str;
}

bool ActivityUser::validate_signIn() {
    // TODO добавить еще разные проверки
    auto end = context_.end();
    if((context_.find("login") == end) ||
       (context_.find("password") == end))

        return false;

    return true;
}

// TODO вернуться когда будет готов интерфейс сессии
// сохранение в базу данных сессии
void ActivityUser::save_session(int& id_user, std::string& str_session) {
//    typename DBSession::Session session(id, str_session);
//    DBSession::add(session);
}
