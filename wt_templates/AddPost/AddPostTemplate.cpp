#include "AddPostTemplate.h"

using namespace NL::Template;

AddPostTemplate::AddPostTemplate(Context& context) : BaseTemplate(context) {

}

std::string & AddPostTemplate::getHTML() {
    LoaderFile loader;
    Template temp(loader);
    temp.load(ADD_POST_WAY);

    //---------------logged block--------------------
    setRightBlock(temp);

    //---------------right  block--------------------
    setRightBlock(temp);

    std::stringstream os;
    temp.render(os);
    addPostHTML = os.str();
    return addPostHTML;
}