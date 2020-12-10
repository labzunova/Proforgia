#include "SignUpTemplate.h"

using namespace NL::Template;

SignUpTemplate::SignUpTemplate() {

}

std::string& SignUpTemplate::getSignUpHTML() {
    LoaderFile loader;
    Template temp(loader);
    temp.load("../wt_templates/templates/signup.html");
    std::stringstream os;
    temp.render(os);
    signUpHTML = os.str();
    return signUpHTML;
}