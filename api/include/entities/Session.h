#pragma once

#include "User.h"
#include <string>

class Session {
public:
    Session(int user_id, std::string user_password, int life_time)
        : user_id_(user_id)
        , user_password_(user_password)
        , life_time_(life_time) {};
    Session();

    User GetUser();
    int Save();
    int Fill();
    int Remove();

private:
    int time_start_;
    int life_time_;
    std::string session_;
    int user_id_;
    std::string user_password_;
};
