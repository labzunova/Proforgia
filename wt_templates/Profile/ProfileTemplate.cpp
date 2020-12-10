#include "ProfileTemplate.h"

using namespace NL::Template;

ProfileTemplate::ProfileTemplate(Context& context) : BaseTemplate(context) {
    //auto username = context.at("username");

}

std::string& ProfileTemplate::getHTML() {
    LoaderFile loader;
    Template temp(loader);

    temp.load("../wt_templates/templates/profile.html");

    std::string username = "cmorrec";
    auto& block_logged = temp.block("logged_fragment");
    block_logged.set("username", username);
    block_logged.set("avatar_res", "aaaaaaaaaaaaaaaaavvvvvvvvvvvvvaaaaaaaaaaaaaa");

    temp.block( "rooms" ).repeat( 3 );
    for (int i = 0; i < 3; i++) {
        temp.block("rooms")[i].set("room_name", "room");
        temp.block("rooms")[i].set("room_src", "room-src");
    }


    std::stringstream os;
    temp.render(os);
    profileHTML = os.str();
    return profileHTML;
}