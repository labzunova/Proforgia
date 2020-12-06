//
// Created by Иван on 24.11.2020.
//
#include <iostream>
#include "../include/Wrappers/DBWrapperRealisations/PostgreDBWrapper.h"

// TODO: допродумать над системой ошибок и исключчений у меня
// TODO: do shared ptr for PGconn
// TODO: do smart ptr for PGresult
// TODO: сформировать свою либу в cmake
DBUser PostgreDBWrapper::get_user_info(const int &user_id, ErrorCodes &error) const {
    PGconn* connection;
    try {
        connection = get_connection();
    }
    catch(std::exception &exc) {
        error = ErrorCodes::DB_CONNECTION_ERROR;
        std::cout << exc.what();
    }

    std::string uid = std::to_string(user_id);
    std::string query = "select * from users where id=" + uid + ";";

    PGresult* result = PQexec(connection, query.c_str());

    if (PQresultStatus(result) != PGRES_TUPLES_OK)
        throw std::runtime_error(PQresultErrorMessage(result));

    if (PQntuples(result) == 0)
        throw std::runtime_error("запись не найдена"); // !
    else {
        int id = std::stoi(PQgetvalue(result, 0, 0));
        std::string nickname = PQgetvalue(result, 0, 1);
        std::string email = PQgetvalue(result, 0, 2);
        std::string date = PQgetvalue(result, 0, 3);

        PQclear(result);
        return std::move(DBUser(id, nickname, date, email));
    }
}

PGconn* PostgreDBWrapper::get_connection() const {
    // TODO: remove hardcode
    std::string connInfo = "host=localhost port=5432 dbname=proforgia_db user=proforgia_user password=password";
    PGconn* connection = PQconnectdb(connInfo.c_str());

    // doesn't work, some issue with shared_ptr
    // std::shared_ptr<PGconn> connection;
    // connection.reset(PQconnectdb(connInfo));

    if (PQstatus(connection) != CONNECTION_OK)
        throw std::runtime_error(PQerrorMessage(connection));

    return connection;
}
