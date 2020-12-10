#include <fstream>
#include "LoginTemplate.h"

using namespace NL::Template;

LoginTemplate::LoginTemplate(Context& context) : BaseTemplate(context) {

}

std::string& LoginTemplate::getHTML() {
    LoaderFile loader;
    Template temp(loader);

    temp.load("../wt_templates/templates/login.html");

    auto& block_logged = temp.block("logged_fragment");
    block_logged.disable();

    std::stringstream os;
    temp.render(os);
    loginHTML = os.str();
    return loginHTML;
}
