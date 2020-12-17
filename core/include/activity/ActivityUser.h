//
// Created by sergei on 28.11.2020.
//

#pragma once

#include "ActivityManager.h"
#include <map>
#include <string>
#include "ErrorCodes.h"

using std::string;

class ActivityUser : public ActivityManager {
public:
    explicit ActivityUser(ContextMap& context);
    ~ActivityUser() override = default;
    ActivityUser(const ActivityUser&) = delete;
    ActivityUser& operator = (ActivityUser&) = delete;

    Status signUp(string& session) override;

    Status login(string& session) override;

private:
    bool validate_signUp();
    bool validate_signIn();
    string create_session();
    void save_session(int& id_user, string& str_session);
};
