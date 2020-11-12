#include "UserApi.h"

std::string UserApi::GetLoginPage() {
    view_.SetPage(View::LOGIN);
    return view_.Render();
}

std::string UserApi::GetRegPage() {
    view_.SetPage(View::REG);
    return view_.Render();
}

User UserApi::SignIn(std::string email, std::string password) {
    User user(email, password);
    user.Fill();

    return user;
}

void UserApi::SignUp(User user) {
    user.Save();
}
