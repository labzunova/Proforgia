#include <fstream>
#include "LoginTemplate.h"

using namespace NL::Template;

LoginTemplate::LoginTemplate() {

}

std::string& LoginTemplate::getHTML() {
    LoaderFile loader;
    Template temp(loader);
    temp.load("../wt_templates/templates/login.html");
    std::stringstream os;
    temp.render(os);
    loginHTML = os.str();
    return loginHTML;
}
