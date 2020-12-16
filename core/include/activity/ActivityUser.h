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

    Status signUp() override;

    Status signIn() override;

private:
    bool validate_signUp();
    bool validate_signIn();
    string create_session(const int& id);
};
