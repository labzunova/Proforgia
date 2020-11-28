//
// Created by sergei on 28.11.2020.
//

#pragma once

#include "ActivityManager.h"
#include "entities/User.h"
#include <map>
#include <string>

using std::string;

class ActivityCustomer : public ActivityManager {
public:
    ActivityCustomer(std::map<string, string> &context, const User &user);
    ~ActivityCustomer() = default;
    ActivityCustomer(const ActivityCustomer&) = delete;
    ActivityCustomer& operator = (ActivityCustomer&) = delete;

private:
    void delete_session();
    void add_tags_room();

public:
    Status exit() override;

    Status add_room() override;

    Status add_content() override;

    Status create_room() override;

    Status remove_room() override;

    Status add_favorite() override;

    Status add_deadline() override;

private:
    User user_;
};
