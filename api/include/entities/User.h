#pragma once

#include <string>
#include <vector>

class User {
public:
    User() = default;
    User(std::string email, std::string password)
        : email_(email)
        , password_(password) {};

    int Save();
    int Update();
    int Fill();

    int getId() {
        return id_;
    }

    std::vector<int> GetRoom() {
        return room_id_;
    };

private:
    std::vector<int> room_id_;
    int id_;
    std::string name_;
    std::string surname_;
    std::string email_;
    std::string password_;
};
