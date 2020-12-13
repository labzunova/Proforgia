#include "ProfileTemplate.h"

using namespace NL::Template;

ProfileTemplate::ProfileTemplate(Context& context) : BaseTemplate(context) {
    //auto username = context.at("username");

}

std::string& ProfileTemplate::getHTML() {
    LoaderFile loader;
    Template temp(loader);

    temp.load("../wt_templates/templates/profile.html");

    //---------------logged block--------------------
    std::string username = "cmorrec";
    auto& block_logged = temp.block("logged_block");
    block_logged.set("username", username);
    block_logged.set("avatar_res", "aaaaaaaaaaaaaaaaavvvvvvvvvvvvvaaaaaaaaaaaaaa");

    //---------------rooms block--------------------
    temp.block( "rooms" ).repeat( 3 );
    for (int i = 0; i < 3; i++) {
        temp.block("rooms")[i].set("room_name", "room");
        temp.block("rooms")[i].set("room_src", "room-src");
    }

    //---------------right  block--------------------
    std::vector<std::string> right_tags = {"Термодед", "Случайный дед", "ОБЖ", "Стройсмех", "Базы данных"};
    auto& block_right = temp.block("right_block.tags");
    block_right.repeat(right_tags.size());
    for (int i = 0; i < right_tags.size(); i++)
        block_right[i].set("tag", right_tags[i]);


    std::stringstream os;
    temp.render(os);
    profileHTML = os.str();
    return profileHTML;
}