//
// Created by sergei on 28.11.2020.
//

#pragma once

#include "ActivityManager.h"
#include "entities/User.h"
#include "entities/Session.h"
#include <map>
#include <string>

using std::string;

class ActivityUser : public ActivityManager {
public:
    explicit ActivityUser(std::map<string, string>& context);
    ~ActivityUser() = default;
    ActivityUser(const ActivityUser&) = delete;
    ActivityUser& operator = (ActivityUser&) = delete;

    Status signUp() override;

    Status signIn() override;

private:
    bool is_email(const string& email) const;
    User get_user(const string& email, const string& password);
    User create_user(const std::map<string, string>& info);
    Session create_session(const User& user);
};
