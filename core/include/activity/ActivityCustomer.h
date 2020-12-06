//
// Created by sergei on 28.11.2020.
//

#pragma once

#include "ActivityManager.h"
#include <map>
#include <string>

using std::string;

template<class User, class Room, class Session>
class ActivityCustomer : public ActivityManager {
public:
    ActivityCustomer(Context &context, User user);
    ~ActivityCustomer() override = default;
    ActivityCustomer(const ActivityCustomer&) = delete;
    ActivityCustomer& operator = (ActivityCustomer&) = delete;

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
