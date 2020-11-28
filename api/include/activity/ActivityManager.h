//
// Created by sergei on 28.11.2020.
//

#pragma once

#include <map>
#include <string>

using std::string;

class ActivityManager {
public:
    enum Status {
        OK,
        SERVER_ERROR,
        CLIENT_ERROR,
    };

protected:
    explicit ActivityManager(std::map<string, string>& context) : context_(context) {};
    ~ActivityManager() = default;

public:
    virtual Status signUp();
    virtual Status signIn();
    virtual Status exit();
    virtual Status add_room();
    virtual Status add_content();
    virtual Status create_room();
    virtual Status remove_room();
    virtual Status add_favorite();
    virtual Status add_deadline();

protected:
    std::map<string, string> context_;
};
