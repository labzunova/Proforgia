#pragma once

#include "external_api/View.h"
#include "entities/User.h"

class UserApi {
public:
    UserApi(View view) : view_(view) {};

    std::string GetLoginPage();
    std::string GetRegPage();
    void SignUp(User user);
    User SignIn(std::string email, std::string password);

protected:
    View view_;
};
