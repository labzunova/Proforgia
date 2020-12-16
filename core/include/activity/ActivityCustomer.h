//
// Created by sergei on 28.11.2020.
//

#pragma once

#include "ActivityManager.h"
#include <map>
#include <string>
#include "DBEntities.h"

using std::string;

class ActivityCustomer : public ActivityManager {
public:
    ActivityCustomer(ContextMap &context, shared_ptr<DBUser> user);
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
    std::shared_ptr<DBUser> user_;
};
