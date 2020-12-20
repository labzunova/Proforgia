//
// Created by sergei on 28.11.2020.
//

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
    ab_digest[SHA_DIGEST_LENGTH - 1] = 0;

    std::string hash_pas = std::string((char*)ab_digest);
    for (int i = 0; i < SHA_DIGEST_LENGTH - 1; ++i)
        hash_pas[i] = abs(hash_pas[i]) % 93 + 33;

    return hash_pas;
}

ActivityManager::Status ActivityUser::signUp(std::string& session) {
    if(!validate_signUp())
        return CLIENT_ERROR;

    std::string login = context_["login"];
    std::string email = context_["mail"];

    ErrorCodes er;
    if (DBUser::get(login, er))
        return CLIENT_ERROR;


    BOOST_LOG_TRIVIAL(debug) << std::to_string(context_["password"].size());
    std::string password = SHA(context_["password"]);
    typename DBUser::User user(login, email, password);
    BOOST_LOG_TRIVIAL(debug) << "Password: " + password;

    bool ex = DBUser::add(user, er);

    if (!ex)
        return SERVER_ERROR;

    auto db_user = DBUser::get(login, er);
    int id_user = db_user->get_id(); // TODO как то по другому получить id

    session = create_session();
    save_session(id_user, session);
    return OK;
}

ActivityManager::Status ActivityUser::login(std::string& session) {
    if(!validate_signIn())
        return CLIENT_ERROR;

    std::string login = context_["login"];

    std::string password = SHA(context_["password"]);
    ErrorCodes er;
    auto user = DBUser::get(login, er);
    if (!user) {
        if (er == DB_ENTITY_NOT_FOUND)
            return CLIENT_ERROR;
        else
            return SERVER_ERROR;
    }
    if(user->password != password)
        return CLIENT_ERROR;

    int id_user = user->get_id();

    session = create_session();
    save_session(id_user, session);
    return OK;
}

ActivityUser::ActivityUser(ContextMap &context) : ActivityManager(context) {
}

// валидация при регистрации
bool ActivityUser::validate_signUp() {
    auto end = context_.end();
    if((context_.find("login") == end) ||
        (context_.find("password") == end) ||
        (context_.find("mail") == end))

        return false;

    if(context_["password"].size() < 4) // проверка на длину пароля
        return false;

    auto mail = context_["mail"];
    if(mail.find('@') == std::string::npos)
        return false;

    return true;
}

// создание случайных символов для сессии
string ActivityUser::create_session() {
    const int size_session = 40; // длина строки сессии

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

// валидация при входе
bool ActivityUser::validate_signIn() {
    auto end = context_.end();
    if((context_.find("login") == end) ||
       (context_.find("password") == end))

        return false;

    return true;
}

// сохранение в базу данных сессии
void ActivityUser::save_session(int& id_user, std::string& str_session) {
    typename DBSession::Session session(str_session, id_user);

    ErrorCodes er;
    DBSession::add(session, er);
}
