//
// Created by sergei on 28.11.2020.
//

#pragma once

#include <map>
#include <string>
#include <utility>

using std::string;

typedef std::map<std::string, std::string> Context;

class ActivityManager {
public:
    enum Status {
        OK,
        SERVER_ERROR,
        CLIENT_ERROR,
    };

protected:
    explicit ActivityManager(Context& context) : context_(std::move(context)) {};

public:
    virtual ~ActivityManager() = default;

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
    Context context_;
};
