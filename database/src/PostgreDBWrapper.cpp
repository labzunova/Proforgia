//
// Created by Иван on 24.11.2020.
//
#include <iostream>
#include "../include/Wrappers/DBWrapperRealisations/PostgreDBWrapper.h"

#include "boost/date_time/local_time/local_time.hpp"

using namespace boost::local_time;
using namespace boost::posix_time;

using std::string;
using std::shared_ptr;

const static string DB_HOST = "localhost";
const static string DB_PORT = "5432";
const static string DB_NAME = "proforgia_db";
const static string DB_USER = "proforgia_user";
const static string DB_USER_PASSWORD = "password";

// TODO: попробовать заводить PGconn только при создании PostgreDBWrapper, чекать что он рабочий при каждом вызове
//  и переподключаться лениво, если с ним что то будет не так и протестить такой вариант работы

// TODO: сделать лог дебага и туда писать PQresultErrorMessage

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

// TODO: переделать, чтобы работала для всех форматов с зоной через нахождение подстроки +/- например
// !!! работает только для формата "2020-12-08 22:39:52.074377+03" (дефолтный формат timestamp with timezone в Postgres)
// для остальных форматов в БД буст будет кидать эксепшен,
// поэтому хранить только автоматически созданный timestamp или строго в это формате
local_date_time parse_timestamp_to_local_date_time(string& str) {
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

shared_ptr<DBRoom> PostgreDBWrapper::get_room_info(const int& room_id, ErrorCodes &error) const {
    std::shared_ptr<PGconn> connection;
    try {
        connection = get_connection();
    }
    catch(std::exception &exc) {
        error = ErrorCodes::DB_CONNECTION_ERROR;
        std::cout << exc.what();
        return nullptr;
    }

    std::string s_id = std::to_string(room_id);
    std::string query = "select * from rooms where id=" + s_id + ";";

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
        string date = PQgetvalue(result.get(), 0, 1);
        string name = PQgetvalue(result.get(), 0, 2);
        string description = PQgetvalue(result.get(), 0, 3);

        return std::make_shared<DBRoom>(id, name, description, date);
    }
}

bool PostgreDBWrapper::add_room(const DBRoom::Room &room_info, ErrorCodes &error) {
    std::shared_ptr<PGconn> connection;
    try {
        connection = get_connection();
    }
    catch(std::exception &exc) {
        error = ErrorCodes::DB_CONNECTION_ERROR;
        std::cout << exc.what();
        return false;
    }

    string query = "insert into rooms (room_name, room_desciption) values "
                   "('" + room_info.room_name +
                   "', '" + room_info.description + "');";

    auto res_deleter = [](PGresult* r) { PQclear(r);};
    std::unique_ptr <PGresult, decltype(res_deleter)> result(PQexec(connection.get(), query.c_str()), res_deleter);
    if (PQresultStatus(result.get()) != PGRES_COMMAND_OK) {
        error = ErrorCodes::UNKNOWN_DB_ERROR;
        return false;
    }

    return true;
}

bool PostgreDBWrapper::remove_room(const int &room_id, ErrorCodes &error) {
    std::shared_ptr<PGconn> connection;
    try {
        connection = get_connection();
    }
    catch(std::exception &exc) {
        error = ErrorCodes::DB_CONNECTION_ERROR;
        std::cout << exc.what();
        return false;
    }

    string s_id = std::to_string(room_id);
    string query = "delete from rooms where id=" + s_id + ";";

    auto res_deleter = [](PGresult* r) { PQclear(r);};
    std::unique_ptr <PGresult, decltype(res_deleter)> result(PQexec(connection.get(), query.c_str()), res_deleter);
    if (PQresultStatus(result.get()) != PGRES_COMMAND_OK) {
        error = ErrorCodes::UNKNOWN_DB_ERROR;
        return false;
    }

    return true;
}

bool PostgreDBWrapper::edit_room(const int& id, const DBRoom::Room &room_info, ErrorCodes &error) {
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
    string query = "update rooms set room_name='" + room_info.room_name + "', room_desciption='" + room_info.description + "' where id=" + s_id + ";";

    auto res_deleter = [](PGresult* r) { PQclear(r);};
    std::unique_ptr <PGresult, decltype(res_deleter)> result(PQexec(connection.get(), query.c_str()), res_deleter);
    if (PQresultStatus(result.get()) != PGRES_COMMAND_OK) {
        error = ErrorCodes::UNKNOWN_DB_ERROR;
        return false;
    }

    return true;
}

bool PostgreDBWrapper::remove_user_from_room(const int &room_id, const int &user_id, ErrorCodes &error) {
    std::shared_ptr<PGconn> connection;
    try {
        connection = get_connection();
    }
    catch(std::exception &exc) {
        error = ErrorCodes::DB_CONNECTION_ERROR;
        std::cout << exc.what();
        return false;
    }

    string s_room_id = std::to_string(room_id);
    string s_user_id = std::to_string(user_id);
    string query = "delete from users_to_rooms where room_id=" + s_room_id + " and user_id=" + s_user_id + ";";

    auto res_deleter = [](PGresult* r) { PQclear(r); };
    std::unique_ptr <PGresult, decltype(res_deleter)> result(PQexec(connection.get(), query.c_str()), res_deleter);
    if (PQresultStatus(result.get()) != PGRES_COMMAND_OK) {
        error = ErrorCodes::UNKNOWN_DB_ERROR;
        return false;
    }

    return true;
}

bool PostgreDBWrapper::add_user_to_room(const int &room_id, const int &user_id, Rights user_rights, ErrorCodes &error) {
    std::shared_ptr<PGconn> connection;
    try {
        connection = get_connection();
    }
    catch(std::exception &exc) {
        error = ErrorCodes::DB_CONNECTION_ERROR;
        std::cout << exc.what();
        return false;
    }

    string s_id_user = std::to_string(user_id);
    string s_id_room = std::to_string(room_id);
    string s_rights;
    user_rights == Rights::ADMIN ? s_rights = "admin" : s_rights = "user";
    string query = "insert into users_to_rooms (user_id, room_id, user_rights) values "
                   "(" + s_id_user +
                   ", " + s_id_room + ", '" + s_rights + "');";

    auto res_deleter = [](PGresult* r) { PQclear(r);};
    std::unique_ptr <PGresult, decltype(res_deleter)> result(PQexec(connection.get(), query.c_str()), res_deleter);
    if (PQresultStatus(result.get()) != PGRES_COMMAND_OK) {
        error = ErrorCodes::UNKNOWN_DB_ERROR;
        return false;
    }

    return true;
}

std::optional<vector<pair<DBUser, Rights>>>
PostgreDBWrapper::get_room_users(const int &room_id, ErrorCodes &error) const {
    std::shared_ptr<PGconn> connection;
    try {
        connection = get_connection();
    }
    catch(std::exception &exc) {
        error = ErrorCodes::DB_CONNECTION_ERROR;
        std::cout << exc.what();
        return std::nullopt;
    }

    string s_id = std::to_string(room_id);
    string query = "select r.*, ur.user_rights from users_to_rooms ur left join users r on ur.user_id=r.id where ur.room_id=" + s_id + ";";

    auto res_deleter = [](PGresult* r) { PQclear(r);};
    std::unique_ptr <PGresult, decltype(res_deleter)> result(PQexec(connection.get(), query.c_str()), res_deleter);

    if (PQresultStatus(result.get()) != PGRES_TUPLES_OK) {
        error = ErrorCodes::UNKNOWN_DB_ERROR;
        return std::nullopt;
    }

    vector<pair<DBUser, Rights>> res;
    int number_of_rows = PQntuples(result.get());
    for (int i = 0; i < number_of_rows; i++) {
        int user_id = std::stoi(PQgetvalue(result.get(), i, 0));
        string nickname = PQgetvalue(result.get(), i, 1);
        string email = PQgetvalue(result.get(), i, 2);
        string registration_time = PQgetvalue(result.get(), i, 3);
        string password = PQgetvalue(result.get(), i, 4);
        string user_rights_s = PQgetvalue(result.get(), i, 5);
        Rights user_rights;
        if (user_rights_s == ADMIN_RIGHTS_DB_STR)
            user_rights = Rights::ADMIN;
        else if (user_rights_s == MEMBER_RIGHTS_DB_STR)
            user_rights = Rights::MEMBER;
        else assert(false);

        res.emplace_back(std::make_pair(
                DBUser(user_id, nickname, registration_time, email, password), user_rights
                ));
    }

    return res;
}

std::optional<vector<DBPost> > PostgreDBWrapper::get_room_posts(const int &room_id, ErrorCodes &error) const {
    std::shared_ptr<PGconn> connection;
    try {
        connection = get_connection();
    }
    catch(std::exception &exc) {
        error = ErrorCodes::DB_CONNECTION_ERROR;
        std::cout << exc.what();
        return std::nullopt;
    }

    string s_id = std::to_string(room_id);
    string query = "select * from posts where room_id=" + s_id + ";";

    auto res_deleter = [](PGresult* r) { PQclear(r);};
    std::unique_ptr <PGresult, decltype(res_deleter)> result(PQexec(connection.get(), query.c_str()), res_deleter);

    if (PQresultStatus(result.get()) != PGRES_TUPLES_OK) {
        error = ErrorCodes::UNKNOWN_DB_ERROR;
        return std::nullopt;
    }

    vector<DBPost> res;
    int number_of_rows = PQntuples(result.get());
    for (int i = 0; i < number_of_rows; i++) {
        int post_id = std::stoi(PQgetvalue(result.get(), i, 0));
        string s_create_time = PQgetvalue(result.get(), i, 1);
        auto create_time = parse_timestamp_to_local_date_time(s_create_time);
        int user_id = std::stoi(PQgetvalue(result.get(), i, 2));
        int _room_id = std::stoi(PQgetvalue(result.get(), i, 3));
        string title = PQgetvalue(result.get(), i, 4);
        string text = PQgetvalue(result.get(), i, 5);

        res.emplace_back(post_id, _room_id, user_id, title, text, create_time);
    }

    return res;
}


std::optional<vector<DBTag> > PostgreDBWrapper::get_room_tags(const int &room_id, ErrorCodes &error) const {

}


