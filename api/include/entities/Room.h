#pragma once

#include "File.h"
#include <vector>

class Room {
public:
    Room(int id) : id_(id) {}

    Room(int adminId, int id, const std::vector<int> &userId)
    : admin_id_(adminId)
    , id_(id)
    , user_id(userId) {};


    int Save();
    int Fill();
    int AddFile(File);

    const std::vector<File> &getFiles() const {
        return files_;
    }

    int getAdminId() const {
        return admin_id_;
    }

    int getId() const {
        return id_;
    }

    const std::vector<int> &getUserId() const {
        return user_id;
    }

private:
    std::vector<File> files_;
    int admin_id_;
    int id_;
    std::vector<int> user_id;
};
