#include "AddPostTemplate.h"

using namespace NL::Template;

AddPostTemplate::AddPostTemplate(Context& context) : BaseTemplate(context) {

}

std::string & AddPostTemplate::getHTML() {
    LoaderFile loader;
    Template temp(loader);
    temp.load("../wt_templates/templates/add_post.html");

    //---------------logged block--------------------
    setRightBlock(temp);

    //---------------right  block--------------------
    setRightBlock(temp);

    std::stringstream os;
    temp.render(os);
    addPostHTML = os.str();
    return addPostHTML;
}