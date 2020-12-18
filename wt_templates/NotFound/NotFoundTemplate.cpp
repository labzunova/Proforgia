#include "NotFoundTemplate.h"

NotFoundTemplate::NotFoundTemplate(Context& context) : BaseTemplate(context) {

}

std::string & NotFoundTemplate::getHTML() {
    LoaderFile loader;
    Template temp(loader);

    temp.load("../wt_templates/templates/not_found.html");

    offLoggedNavBar(temp);

    std::stringstream os;
    temp.render(os);
    notFoundHTML = os.str();
    return notFoundHTML;
}