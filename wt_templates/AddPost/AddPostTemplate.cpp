#include "AddPostTemplate.h"

using namespace NL::Template;

AddPostTemplate::AddPostTemplate(Context& context) : BaseTemplate(context) {

}

std::string & AddPostTemplate::getHTML() {
    LoaderFile loader;
    Template temp(loader);
    temp.load("../wt_templates/templates/add_post.html");

    //---------------logged block--------------------
    std::string username = "cmorrec";
    auto& block_logged = temp.block("logged_block");
    block_logged.set("username", username);
    block_logged.set("avatar_res", "aaaaaaaaaaaaaaaaavvvvvvvvvvvvvaaaaaaaaaaaaaa");

    //---------------right  block--------------------
    std::vector<std::string> right_tags = {"Термодед", "Случайный дед", "ОБЖ", "Стройсмех", "Базы данных"};
    auto& block_right = temp.block("right_block.tags");
    block_right.repeat(right_tags.size());
    for (int i = 0; i < right_tags.size(); i++)
        block_right[i].set("tag", right_tags[i]);

    std::stringstream os;
    temp.render(os);
    addPostHTML = os.str();
    return addPostHTML;
}