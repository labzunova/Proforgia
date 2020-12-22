#include <fstream>
#include "LoginTemplate.h"

using namespace NL::Template;

LoginTemplate::LoginTemplate(Context& context) : BaseTemplate(context) {

}

std::string& LoginTemplate::getHTML() {
    LoaderFile loader;
    Template temp(loader);

    temp.load("../wt_templates/templates/login.html");

    temp.load(LOGIN_WAY);

    offLoggedNavBar(temp);

    std::stringstream os;
    temp.render(os);
    loginHTML = os.str();
    return loginHTML;
}
