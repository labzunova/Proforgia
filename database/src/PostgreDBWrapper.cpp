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
// TODO: использовать один PQResult для записи нового результата при нескольких запросах

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

    string query = "insert into rooms (room_name, room_description) values "
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
    string query = "update rooms set room_name='" + room_info.room_name + "', room_description='" + room_info.description + "' where id=" + s_id + ";";

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
    string query = "select * from tags where room_id=" + s_id + ";";

    auto res_deleter = [](PGresult* r) { PQclear(r);};
    std::unique_ptr <PGresult, decltype(res_deleter)> result(PQexec(connection.get(), query.c_str()), res_deleter);

    if (PQresultStatus(result.get()) != PGRES_TUPLES_OK) {
        error = ErrorCodes::UNKNOWN_DB_ERROR;
        return std::nullopt;
    }

    vector<DBTag> res;
    int number_of_rows = PQntuples(result.get());
    for (int i = 0; i < number_of_rows; i++) {
        int tag_id = std::stoi(PQgetvalue(result.get(), i, 0));
        string tag_name = PQgetvalue(result.get(), i, 1);
        int _room_id = std::stoi(PQgetvalue(result.get(), i, 2));

        res.emplace_back(tag_id, tag_name, _room_id);
    }

    return res;
}

// TODO: в БД нет проверки на то что пост может быть добавлен только юзером который состоит в комнате room_id
bool PostgreDBWrapper::add_post(const DBPost::Post &post_info, ErrorCodes &error) {
    std::shared_ptr<PGconn> connection;
    try {
        connection = get_connection();
    }
    catch(std::exception &exc) {
        error = ErrorCodes::DB_CONNECTION_ERROR;
        std::cout << exc.what();
        return false;
    }

    string s_user_id = std::to_string(post_info.user_id);
    string s_room_id = std::to_string(post_info.room_id);
    string query = "insert into posts (user_id, room_id, title, post_text) values "
                   "(" + s_user_id +
                   ", " + s_room_id +
                   ", '" + post_info.title +
                   "', '" + post_info.text + "');";

    auto res_deleter = [](PGresult* r) { PQclear(r);};
    std::unique_ptr <PGresult, decltype(res_deleter)> result(PQexec(connection.get(), query.c_str()), res_deleter);
    if (PQresultStatus(result.get()) != PGRES_COMMAND_OK) {
        error = ErrorCodes::UNKNOWN_DB_ERROR;
        return false;
    }

    return true;
}

bool PostgreDBWrapper::remove_post(const int &post_id, ErrorCodes &error) {
    std::shared_ptr<PGconn> connection;
    try {
        connection = get_connection();
    }
    catch(std::exception &exc) {
        error = ErrorCodes::DB_CONNECTION_ERROR;
        std::cout << exc.what();
        return false;
    }

    string s_id = std::to_string(post_id);
    string query = "delete from posts where id=" + s_id + ";";

    auto res_deleter = [](PGresult* r) { PQclear(r);};
    std::unique_ptr <PGresult, decltype(res_deleter)> result(PQexec(connection.get(), query.c_str()), res_deleter);
    if (PQresultStatus(result.get()) != PGRES_COMMAND_OK) {
        error = ErrorCodes::UNKNOWN_DB_ERROR;
        return false;
    }

    return true;
}

shared_ptr<DBPost> PostgreDBWrapper::get_post_info(const int &post_id, ErrorCodes &error) const {
    std::shared_ptr<PGconn> connection;
    try {
        connection = get_connection();
    }
    catch(std::exception &exc) {
        error = ErrorCodes::DB_CONNECTION_ERROR;
        std::cout << exc.what();
        return nullptr;
    }

    std::string s_id = std::to_string(post_id);
    std::string query = "select * from posts where id=" + s_id + ";";

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
        int _post_id = std::stoi(PQgetvalue(result.get(), 0, 0));
        string s_create_time = PQgetvalue(result.get(), 0, 1);
        auto create_time = parse_timestamp_to_local_date_time(s_create_time);
        int user_id = std::stoi(PQgetvalue(result.get(), 0, 2));
        int _room_id = std::stoi(PQgetvalue(result.get(), 0, 3));
        string title = PQgetvalue(result.get(), 0, 4);
        string text = PQgetvalue(result.get(), 0, 5);

        assert(_post_id == post_id);
        return std::make_shared<DBPost>(_post_id, _room_id, user_id, title, text, create_time);
    }
}

bool PostgreDBWrapper::edit_post(const int& id, const DBPost::Post &post_info, ErrorCodes &error) {
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
    string query = "update posts set title='" + post_info.title + "', post_text='" + post_info.text + "' where id=" + s_id + ";";

    auto res_deleter = [](PGresult* r) { PQclear(r);};
    std::unique_ptr <PGresult, decltype(res_deleter)> result(PQexec(connection.get(), query.c_str()), res_deleter);
    if (PQresultStatus(result.get()) != PGRES_COMMAND_OK) {
        error = ErrorCodes::UNKNOWN_DB_ERROR;
        return false;
    }

    return true;
}

std::optional<vector<int> >
PostgreDBWrapper::get_posts_by_tags(vector<std::string> &_tags, int room_id, ErrorCodes &error) const {
    std::shared_ptr<PGconn> connection;
    try {
        connection = get_connection();
    }
    catch(std::exception &exc) {
        error = ErrorCodes::DB_CONNECTION_ERROR;
        std::cout << exc.what();
        return std::nullopt;
    }

    // итоговый результат
    vector<int> result_posts_ids;

    // получаю все тэги этой комнаты и помещаю их в map
    std::string s_id = std::to_string(room_id);
    std::string query = "select id, tag_name from tags where room_id=" + s_id + ";";
    auto res_deleter = [](PGresult* r) { PQclear(r);};
    std::unique_ptr <PGresult, decltype(res_deleter)> room_tags_result(PQexec(connection.get(), query.c_str()), res_deleter);
    if (PQresultStatus(room_tags_result.get()) != PGRES_TUPLES_OK) {
        error = ErrorCodes::UNKNOWN_DB_ERROR;
        return std::nullopt;
    }
    std::unordered_map<string, int> room_tags = {};
    int number_of_rows = PQntuples(room_tags_result.get());
    if (number_of_rows == 0) return result_posts_ids;
    for (int i = 0; i < number_of_rows; i++) {
        int tag_id = std::stoi(PQgetvalue(room_tags_result.get(), i, 0));
        string tag_name = PQgetvalue(room_tags_result.get(), i, 1);

        room_tags.insert({tag_name, tag_id});
    }

    // заполняю массив id'шников всех тэгов из _tags которые состоят в комнате room_id
    vector<int> _tags_ids = {};
    for (auto & _tag : _tags) {
        auto tag = room_tags.find(_tag);
        if (tag != room_tags.end()) _tags_ids.push_back(tag->second);
    }

    // делаю запрос на нахождение id постов у которых есть ВСЕ тэги из _tags
    if (_tags_ids.empty()) return result_posts_ids;
    string _query = "select p1.post_id from tags_to_posts p1 ";
    string joining;
    string condition = "where p1.tag_id = " + std::to_string(_tags_ids[0]);
    for (int i = 1; i < _tags_ids.size(); i++) {
        joining += "left join tags_to_posts p" + std::to_string(i+1) +
                " on p" + std::to_string(i) + ".post_id = p" + std::to_string(i+1) + ".post_id ";
        condition += " and p" + std::to_string(i+1) + ".tag_id = " + std::to_string(_tags_ids[i]);
    }
    // QUERY EXAMPLE:
    // select p1.post_id from tags_to_posts p1 left join tags_to_posts p2 on p1.post_id = p2.post_id left
    // join tags_to_posts p3 on p3.post_id = p2.post_id
    // where p1.tag_id = 2 and p2.tag_id = 6 and p3.tag_id = 7;
    _query = _query + joining + condition + ";";

    std::unique_ptr <PGresult, decltype(res_deleter)> result(PQexec(connection.get(), _query.c_str()), res_deleter);

    number_of_rows = PQntuples(result.get());
    for (int i = 0; i < number_of_rows; i++) {
        int _post_id = std::stoi(PQgetvalue(result.get(), i, 0));
        result_posts_ids.push_back(_post_id);
    }

    return result_posts_ids;
}

bool PostgreDBWrapper::add_tags_to_post(vector<std::string> &_tags, const int &post_id, const int &room_id, ErrorCodes &error) {
    if (_tags.empty()) return true;

    std::shared_ptr<PGconn> connection;
    try {
        connection = get_connection();
    }
    catch(std::exception &exc) {
        error = ErrorCodes::DB_CONNECTION_ERROR;
        std::cout << exc.what();
        return false;
    }

    // добавить в tags те тэги, которых еще не было в тэгах этой комнаты
    std::string s_id = std::to_string(room_id);
    std::string query = "insert into tags (tag_name, room_id) values ";
    for (int i = 0; i < _tags.size(); i++) {
        query += "('" + _tags[i] + "', " + s_id + ")";
        if (i != (_tags.size() - 1)) query += ", ";
    }
    query += " on conflict do nothing;";

    auto res_deleter = [](PGresult* r) { PQclear(r);};
    std::unique_ptr <PGresult, decltype(res_deleter)> add_tags_result(PQexec(connection.get(), query.c_str()), res_deleter);
    if (PQresultStatus(add_tags_result.get()) != PGRES_COMMAND_OK) {
        error = ErrorCodes::UNKNOWN_DB_ERROR;
        return false;
    }


    // выбрать все тэги этого поста, этой комнаты
    query = "select id from tags where ((tag_name = '" + _tags[0] + "'";;
    for (int i = 1; i < _tags.size(); i++) {
        query += " or tag_name = '" + _tags[i] + "'";
    }
    query += ") and room_id = " + std::to_string(room_id) + ");";

    std::unique_ptr <PGresult, decltype(res_deleter)> get_tags_of_this_post_result(PQexec(connection.get(), query.c_str()), res_deleter);
    if (PQresultStatus(get_tags_of_this_post_result.get()) != PGRES_TUPLES_OK) {
        error = ErrorCodes::UNKNOWN_DB_ERROR;
        return false;
    }

    vector<int> tags_ids;
    int number_of_rows = PQntuples(get_tags_of_this_post_result.get());
    if (number_of_rows == 0) return true;
    for (int i = 0; i < number_of_rows; i++) {
        int id = std::stoi(PQgetvalue(get_tags_of_this_post_result.get(), i, 0));
        tags_ids.push_back(id);
    }

    // очистить все ранние связи этого поста с тэгами
    query = "delete from tags_to_posts where post_id = " + std::to_string(post_id) + ";";
    std::unique_ptr <PGresult, decltype(res_deleter)> delete_post_tags(PQexec(connection.get(), query.c_str()), res_deleter);
    if (PQresultStatus(delete_post_tags.get()) != PGRES_COMMAND_OK) {
        error = ErrorCodes::UNKNOWN_DB_ERROR;
        return false;
    }

    // вставить актуальные записи связей тэгов с этим постом
    if (tags_ids.empty()) return true;
    s_id = std::to_string(room_id);
    query = "insert into tags_to_posts (tag_id, post_id) values (" + std::to_string(tags_ids[0]) + ", " + s_id + ")";
    for (int i = 1; i < tags_ids.size(); i++) {
        query += ", (" + std::to_string(tags_ids[i]) + ", " + s_id + ")";
    }
    query += ";";
    std::unique_ptr <PGresult, decltype(res_deleter)> add_new_post_tags(PQexec(connection.get(), query.c_str()), res_deleter);
    if (PQresultStatus(add_new_post_tags.get()) != PGRES_COMMAND_OK) {
        error = ErrorCodes::UNKNOWN_DB_ERROR;
        return false;
    }

    return true;
}

bool PostgreDBWrapper::add_file(const string &client_name, const string &storage_name, int post_id, ErrorCodes &error) {
    std::shared_ptr<PGconn> connection;
    try {
        connection = get_connection();
    }
    catch(std::exception &exc) {
        error = ErrorCodes::DB_CONNECTION_ERROR;
        std::cout << exc.what();
        return false;
    }

    string query = "insert into files (post_id, filename, filename_storage) values "
                   "(" + std::to_string(post_id) +
                   ", '" + client_name +
                   "', '" + storage_name + "');";

    auto res_deleter = [](PGresult* r) { PQclear(r);};
    std::unique_ptr <PGresult, decltype(res_deleter)> result(PQexec(connection.get(), query.c_str()), res_deleter);
    if (PQresultStatus(result.get()) != PGRES_COMMAND_OK) {
        error = ErrorCodes::UNKNOWN_DB_ERROR;
        return false;
    }

    return true;
}

bool PostgreDBWrapper::remove_file(const std::string& client_name, const std::string& storage_filename, ErrorCodes &error) {
    std::shared_ptr<PGconn> connection;
    try {
        connection = get_connection();
    }
    catch(std::exception &exc) {
        error = ErrorCodes::DB_CONNECTION_ERROR;
        std::cout << exc.what();
        return false;
    }

    string query = "delete from files where filename ='" + client_name + "' and filename_storage = '" + storage_filename + "';";

    auto res_deleter = [](PGresult* r) { PQclear(r);};
    std::unique_ptr <PGresult, decltype(res_deleter)> result(PQexec(connection.get(), query.c_str()), res_deleter);
    if (PQresultStatus(result.get()) != PGRES_COMMAND_OK) {
        error = ErrorCodes::UNKNOWN_DB_ERROR;
        return false;
    }

    return true;
}

shared_ptr<DBTag> PostgreDBWrapper::get_tag_info(const int &tag_id, ErrorCodes &error) const {
    std::shared_ptr<PGconn> connection;
    try {
        connection = get_connection();
    }
    catch(std::exception &exc) {
        error = ErrorCodes::DB_CONNECTION_ERROR;
        std::cout << exc.what();
        return nullptr;
    }

    std::string s_id = std::to_string(tag_id);
    std::string query = "select id, tag_name, room_id from tags where id=" + s_id + ";";

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
    else if (PQntuples(result.get()) > 1) {
        error = ErrorCodes::UNKNOWN_DB_ERROR;
        return nullptr;
    }
    else {
        int id = std::stoi(PQgetvalue(result.get(), 0, 0));
        std::string tag_name = PQgetvalue(result.get(), 0, 1);
        int room_id = std::stoi(PQgetvalue(result.get(), 0, 2));

        return std::make_shared<DBTag>(id, tag_name, room_id);
    }
}

std::optional<vector<int> > PostgreDBWrapper::get_post_tags_ids(int post_id, ErrorCodes &error) const {
    std::shared_ptr<PGconn> connection;
    try {
        connection = get_connection();
    }
    catch(std::exception &exc) {
        error = ErrorCodes::DB_CONNECTION_ERROR;
        std::cout << exc.what();
        return std::nullopt;
    }

    std::string s_id = std::to_string(post_id);
    std::string query = "select tag_id from tags_to_posts where post_id = " + s_id + ";";

    auto res_deleter = [](PGresult* r) { PQclear(r);};
    std::unique_ptr <PGresult, decltype(res_deleter)> result(PQexec(connection.get(), query.c_str()), res_deleter);

    if (PQresultStatus(result.get()) != PGRES_TUPLES_OK) {
        error = ErrorCodes::UNKNOWN_DB_ERROR;
        return std::nullopt;
    }

    std::vector<int> tags_ids;
    int number_of_rows = PQntuples(result.get());
    for (int i = 0; i < number_of_rows; i++) {
        int _tag_id = std::stoi(PQgetvalue(result.get(), i, 0));
        tags_ids.push_back(_tag_id);
    }

    return tags_ids;
}

std::optional<std::vector<std::string> > PostgreDBWrapper::get_post_attachments(int post_id, ErrorCodes &error) const {
    std::shared_ptr<PGconn> connection;
    try {
        connection = get_connection();
    }
    catch(std::exception &exc) {
        error = ErrorCodes::DB_CONNECTION_ERROR;
        std::cout << exc.what();
        return std::nullopt;
    }

    std::string s_id = std::to_string(post_id);
    std::string query = "select filename from files where post_id = " + s_id + ";";

    auto res_deleter = [](PGresult* r) { PQclear(r);};
    std::unique_ptr <PGresult, decltype(res_deleter)> result(PQexec(connection.get(), query.c_str()), res_deleter);

    if (PQresultStatus(result.get()) != PGRES_TUPLES_OK) {
        error = ErrorCodes::UNKNOWN_DB_ERROR;
        return std::nullopt;
    }

    std::vector<std::string> files_names_in_storage;
    int number_of_rows = PQntuples(result.get());
    for (int i = 0; i < number_of_rows; i++) {
        string filename = PQgetvalue(result.get(), i, 0);
        files_names_in_storage.push_back(filename);
    }

    return files_names_in_storage;
}

shared_ptr<DBSession> PostgreDBWrapper::get_session_info(const int &session_id, ErrorCodes &error) const {
    std::shared_ptr<PGconn> connection;
    try {
        connection = get_connection();
    }
    catch(std::exception &exc) {
        error = ErrorCodes::DB_CONNECTION_ERROR;
        std::cout << exc.what();
        return nullptr;
    }

    std::string query = "select * from sessions where id='" + std::to_string(session_id) + "';";

    auto res_deleter = [](PGresult* r) { PQclear(r);};
    std::unique_ptr <PGresult, decltype(res_deleter)> result(PQexec(connection.get(), query.c_str()), res_deleter);

    if ((PQresultStatus(result.get()) != PGRES_TUPLES_OK) && (PQntuples(result.get()) > 1)) {
        error = ErrorCodes::UNKNOWN_DB_ERROR;
        return nullptr;
    }

    if (PQntuples(result.get()) == 0) {
        error = ErrorCodes::DB_ENTITY_NOT_FOUND;
        return nullptr;
    }
    else {
        int id = std::stoi(PQgetvalue(result.get(), 0, 0));
        string session_id_str = PQgetvalue(result.get(), 0, 1);
        int user_id = std::stoi(PQgetvalue(result.get(), 0, 2));
        string create_time = PQgetvalue(result.get(), 0, 3);

        return std::make_shared<DBSession>(id, parse_timestamp_to_local_date_time(create_time), session_id_str, user_id);
    }
}

bool PostgreDBWrapper::remove_session(const int &session_id, ErrorCodes &error) {
    std::shared_ptr<PGconn> connection;
    try {
        connection = get_connection();
    }
    catch(std::exception &exc) {
        error = ErrorCodes::DB_CONNECTION_ERROR;
        std::cout << exc.what();
        return false;
    }

    string s_id = std::to_string(session_id);
    string query = "delete from sessions where id=" + s_id + ";";

    auto res_deleter = [](PGresult* r) { PQclear(r);};
    std::unique_ptr <PGresult, decltype(res_deleter)> result(PQexec(connection.get(), query.c_str()), res_deleter);
    if (PQresultStatus(result.get()) != PGRES_COMMAND_OK) {
        error = ErrorCodes::UNKNOWN_DB_ERROR;
        return false;
    }

    return true;
}

bool PostgreDBWrapper::add_session(const DBSession::Session &session_info, ErrorCodes &error) {
    std::shared_ptr<PGconn> connection;
    try {
        connection = get_connection();
    }
    catch(std::exception &exc) {
        error = ErrorCodes::DB_CONNECTION_ERROR;
        std::cout << exc.what();
        return false;
    }

    string s_user_id = std::to_string(session_info.user_id);
    string query = "insert into sessions (user_id, session_id) values "
                   "(" + s_user_id +
                   ", '" + session_info.session_identificator + "');";

    auto res_deleter = [](PGresult* r) { PQclear(r);};
    std::unique_ptr <PGresult, decltype(res_deleter)> result(PQexec(connection.get(), query.c_str()), res_deleter);
    if (PQresultStatus(result.get()) != PGRES_COMMAND_OK) {
        error = ErrorCodes::UNKNOWN_DB_ERROR;
        return false;
    }

    return true;
}