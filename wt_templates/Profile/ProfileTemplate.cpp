#include "ProfileTemplate.h"

using namespace NL::Template;

ProfileTemplate::ProfileTemplate(Context& context) : BaseTemplate(context) {

}

std::string& ProfileTemplate::getHTML() {
    LoaderFile loader;
    Template temp(loader);

    temp.load("../wt_templates/templates/profile.html");

    //---------------logged block--------------------
    setLoggedNavBar(temp);

    //---------------rooms block--------------------
    auto& roomsBlock = temp.block("rooms" );
    roomsBlock.repeat(context.rooms.size() );
    for (int i = 0; i < context.rooms.size(); i++) {
        roomsBlock[i].set("room_name", context.rooms[i].title);
        roomsBlock[i].set("room_src", context.rooms[i].url);
        if (!context.rooms[i].isAdmin) {
            roomsBlock[i].block("remove_room").disable();
        } else {
            roomsBlock[i].block("remove_room").set("room_name", context.rooms[i].title);
            roomsBlock[i].block("remove_room").set("room_src", context.rooms[i].url);
        }
    }

    std::stringstream os;
    temp.render(os);
    profileHTML = os.str();
    return profileHTML;
}