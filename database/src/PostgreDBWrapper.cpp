//
// Created by Иван on 24.11.2020.
//
#include <iostream>
#include "../include/Wrappers/DBWrapperRealisations/PostgreDBWrapper.h"

using std::string;
using std::shared_ptr;

// TODO: сменить с C-стиля на const static
#define DB_HOST "localhost"
#define DB_PORT "5432"
#define DB_NAME "proforgia_db"
#define DB_USER "proforgia_user"
#define DB_USER_PASSWORD "password"

PostgreDBWrapper::PostgreDBWrapper() :
    host(DB_HOST),
    port(DB_PORT),
    db_name(DB_NAME),
    db_user(DB_USER),
    db_user_password(DB_USER_PASSWORD) {

}

std::shared_ptr<PGconn> PostgreDBWrapper::get_connection() const {
    std::string connInfo = "host=" + host + " port=" + port + " dbname=" + db_name + " user=" + db_user + " password=" + db_user_password;

    std::shared_ptr<PGconn> connection;
    connection.reset(PQconnectdb(connInfo.c_str()), &PQfinish);

    if (PQstatus(connection.get()) != CONNECTION_OK)
        throw std::runtime_error(PQerrorMessage(connection.get()));

    return connection;
}


shared_ptr<DBUser> PostgreDBWrapper::get_user_info(const int &user_id, ErrorCodes &error) const {
    std::shared_ptr<PGconn> connection;
    try {
        connection = get_connection();
    }
    catch(std::exception &exc) {
        error = ErrorCodes::DB_CONNECTION_ERROR;
        std::cout << exc.what();
        return nullptr;
    }

    std::string s_id = std::to_string(user_id);
    std::string query = "select * from users where id=" + s_id + ";";

    auto res_deleter = [](PGresult* r) { PQclear(r);};
    std::unique_ptr <PGresult, decltype(res_deleter)> result(PQexec(connection.get(), query.c_str()), res_deleter);

    if (PQresultStatus(result.get()) != PGRES_TUPLES_OK) {
        error = ErrorCodes::UNKNOWN_DB_ERROR;
        return nullptr;
    }

    if (PQntuples(result.get()) == 0) {
        error = ErrorCodes::DB_ENTITY_NOT_FOUND;
        return nullptr;
    }
    else {
        int id = std::stoi(PQgetvalue(result.get(), 0, 0));
        std::string nickname = PQgetvalue(result.get(), 0, 1);
        std::string email = PQgetvalue(result.get(), 0, 2);
        std::string date = PQgetvalue(result.get(), 0, 3);
        std::string password = PQgetvalue(result.get(), 0, 4);

        return std::make_shared<DBUser>(id, nickname, date, email, password);
    }
}


shared_ptr<DBUser> PostgreDBWrapper::get_user_info(const string &nickname, ErrorCodes &error) const {
    std::shared_ptr<PGconn> connection;
    try {
        connection = get_connection();
    }
    catch(std::exception &exc) {
        error = ErrorCodes::DB_CONNECTION_ERROR;
        std::cout << exc.what();
        return nullptr;
    }

    std::string query = "select * from users where nickname='" + nickname + "';";

    auto res_deleter = [](PGresult* r) { PQclear(r);};
    std::unique_ptr <PGresult, decltype(res_deleter)> result(PQexec(connection.get(), query.c_str()), res_deleter);

    if (PQresultStatus(result.get()) != PGRES_TUPLES_OK) {
        error = ErrorCodes::UNKNOWN_DB_ERROR;
        return nullptr;
    }

    if (PQntuples(result.get()) == 0) {
        error = ErrorCodes::DB_ENTITY_NOT_FOUND;
        return nullptr;
    }
    else {
        int id = std::stoi(PQgetvalue(result.get(), 0, 0));
        std::string nick_name = PQgetvalue(result.get(), 0, 1);
        std::string email = PQgetvalue(result.get(), 0, 2);
        std::string date = PQgetvalue(result.get(), 0, 3);
        std::string password = PQgetvalue(result.get(), 0, 4);

        return std::make_shared<DBUser>(id, nick_name, date, email, password);
    }
}

bool PostgreDBWrapper::add_user(const DBUser::User &user_info, ErrorCodes &error) {
    std::shared_ptr<PGconn> connection;
    try {
        connection = get_connection();
    }
    catch(std::exception &exc) {
        error = ErrorCodes::DB_CONNECTION_ERROR;
        std::cout << exc.what();
        return false;
    }

    string query = "insert into users (nickname, email, password) values "
                   "('" + user_info.nick_name +
            "', '" + user_info.email +
            "', '" + user_info.password + "');";

    auto res_deleter = [](PGresult* r) { PQclear(r);};
    std::unique_ptr <PGresult, decltype(res_deleter)> result(PQexec(connection.get(), query.c_str()), res_deleter);
    if (PQresultStatus(result.get()) != PGRES_COMMAND_OK) {
        error = ErrorCodes::UNKNOWN_DB_ERROR;
        return false;
    }

    return true;
}

bool PostgreDBWrapper::remove_user(const int& user_id, ErrorCodes &error) {
    std::shared_ptr<PGconn> connection;
    try {
        connection = get_connection();
    }
    catch(std::exception &exc) {
        error = ErrorCodes::DB_CONNECTION_ERROR;
        std::cout << exc.what();
        return false;
    }

    string s_id = std::to_string(user_id);
    string query = "delete from users where id=" + s_id + ";";

    auto res_deleter = [](PGresult* r) { PQclear(r);};
    std::unique_ptr <PGresult, decltype(res_deleter)> result(PQexec(connection.get(), query.c_str()), res_deleter);
    if (PQresultStatus(result.get()) != PGRES_COMMAND_OK) {
        error = ErrorCodes::UNKNOWN_DB_ERROR;
        return false;
    }

    return true;
}

bool PostgreDBWrapper::edit_user(const int& id, const DBUser::User &user_info, ErrorCodes &error) {
    std::shared_ptr<PGconn> connection;
    try {
        connection = get_connection();
    }
    catch(std::exception &exc) {
        error = ErrorCodes::DB_CONNECTION_ERROR;
        std::cout << exc.what();
        return false;
    }

    string s_id = std::to_string(id);
    string query = "update users set nickname='" + user_info.nick_name + "', email='" + user_info.email + "' where id=" + s_id + ";";

    auto res_deleter = [](PGresult* r) { PQclear(r);};
    std::unique_ptr <PGresult, decltype(res_deleter)> result(PQexec(connection.get(), query.c_str()), res_deleter);
    if (PQresultStatus(result.get()) != PGRES_COMMAND_OK) {
        error = ErrorCodes::UNKNOWN_DB_ERROR;
        return false;
    }

    return true;
}

std::optional< vector<pair<DBRoom, Rights>> > PostgreDBWrapper::get_user_rooms(const int &user_id, ErrorCodes &error) const {
    std::shared_ptr<PGconn> connection;
    try {
        connection = get_connection();
    }
    catch(std::exception &exc) {
        error = ErrorCodes::DB_CONNECTION_ERROR;
        std::cout << exc.what();
        return std::nullopt;
    }

    string s_id = std::to_string(user_id);
    string query = "select r.*, ur.user_rights from users_to_rooms ur left join rooms r on ur.room_id=r.id where ur.user_id=" + s_id + ";";

    auto res_deleter = [](PGresult* r) { PQclear(r);};
    std::unique_ptr <PGresult, decltype(res_deleter)> result(PQexec(connection.get(), query.c_str()), res_deleter);

    if (PQresultStatus(result.get()) != PGRES_TUPLES_OK) {
        error = ErrorCodes::UNKNOWN_DB_ERROR;
        return std::nullopt;
    }

    vector<pair<DBRoom, Rights>> res;
    int number_of_rows = PQntuples(result.get());
    for (int i = 0; i < number_of_rows; i++) {
        int room_id = std::stoi(PQgetvalue(result.get(), i, 0));
        string date = PQgetvalue(result.get(), i, 1);
        string name = PQgetvalue(result.get(), i, 2);
        string description = PQgetvalue(result.get(), i, 3);
        string user_rights_s = PQgetvalue(result.get(), i, 4);
        Rights user_rights;
        if (user_rights_s == ADMIN_RIGHTS_DB_STR)
            user_rights = Rights::ADMIN;
        else if (user_rights_s == MEMBER_RIGHTS_DB_STR)
            user_rights = Rights::MEMBER;
        else assert(false);

        res.emplace_back(std::make_pair(DBRoom(room_id, name, description, date), user_rights));
    }

    return res;
}


