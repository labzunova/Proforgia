//
// Created by sergei on 28.11.2020.
//

#pragma once

#include <map>
#include <string>
#include <utility>
#include "DBEntities.h"
#include "ErrorCodes.h"

typedef std::map<std::string, std::string> ContextMap;

class ActivityManager {
public:
    enum Status {
        OK,
        SERVER_ERROR,
        CLIENT_ERROR,
    };

protected:
    enum Type {
        IMAGE,
        FILE,
    };

protected:
    explicit ActivityManager(ContextMap& context) : context_(context) {};

public:
    virtual ~ActivityManager() = default;

    virtual Status signUp(std::string& session);
    virtual Status login(std::string& session);
    virtual Status exit();
    virtual Status exit_room();
    virtual Status add_room();
    virtual Status add_content();
    virtual Status create_room();
    virtual Status remove_room();
    virtual Status add_favorite();
    virtual Status add_deadline();

protected:
    ContextMap context_;
};
