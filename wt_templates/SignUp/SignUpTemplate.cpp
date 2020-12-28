#include "SignUpTemplate.h"

using namespace NL::Template;

SignUpTemplate::SignUpTemplate(Context& context) : BaseTemplate(context) {

}

std::string& SignUpTemplate::getHTML() {
    LoaderFile loader;
    Template temp(loader);
    temp.load(SIGNUP_WAY);

    offLoggedNavBar(temp);

    std::stringstream os;
    temp.render(os);
    signUpHTML = os.str();
    return signUpHTML;
}