#pragma once

#include <string>

class File {
public:
    struct Data {
        /* вид в котором храняться файлы */
    };

public:
    File(int id) : id_(id) {};

    File(const int &userId, const Data &data) : user_id_(userId), data_(data) {}

    int Save();
    int Fill();

public:
    int getId() const {
        return id_;
    }

    int getAddTime() const {
        return add_time_;
    }

    const std::string &getUserId() const {
        return nullptr;
    }

    const Data &getData() const {
        return data_;
    }

private:
    int id_;
    int add_time_;
    int user_id_;
    Data data_;
};
