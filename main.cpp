#include <iostream>

#include "wt_templates/Login/LoginTemplate.h"
#include "wt_templates/SignUp/SignUpTemplate.h"

int main(int argc, char* argv[]) {
    std::cout << SignUpTemplate().getSignUpHTML();
    return 0;
}
