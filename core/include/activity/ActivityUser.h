//
// Created by sergei on 28.11.2020.
//

#pragma once

#include "ActivityManager.h"
#include <map>
#include <string>
#include "ErrorCodes.h"

class ActivityUser : public ActivityManager {
public:
    explicit ActivityUser(ContextMap& context);
    ~ActivityUser() override = default;
    ActivityUser(const ActivityUser&) = delete;
    ActivityUser& operator = (ActivityUser&) = delete;

    Status signUp(std::string& session) override;

    Status login(std::string& session) override;

private:
    bool validate_signUp();
    bool validate_signIn();
    std::string create_session();
    void save_session(int& id_user, std::string& str_session);
};
