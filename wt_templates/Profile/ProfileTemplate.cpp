#include "ProfileTemplate.h"

using namespace NL::Template;

ProfileTemplate::ProfileTemplate(Context& context) : BaseTemplate(context) {

}

std::string& ProfileTemplate::getHTML() {
    LoaderFile loader;
    Template temp(loader);

    temp.load(PROFILE_WAY);

    //---------------logged block--------------------
    setLoggedNavBar(temp);

    //---------------rooms block--------------------
    auto& roomsBlock = temp.block(PROFILE_ROOMS_BLOCK);
    roomsBlock.repeat(context.rooms.size() );
    for (int i = 0; i < context.rooms.size(); i++) {
        roomsBlock[i].set(PROFILE_ROOMS_BLOCK_NAME, context.rooms[i].title);
        roomsBlock[i].set(PROFILE_ROOMS_BLOCK_SRC, context.rooms[i].url);
        if (!context.rooms[i].isAdmin) {
            roomsBlock[i].block(PROFILE_ROOMS_BLOCK_REMOVE_BLOCK).disable();
        } else {
            roomsBlock[i].block(PROFILE_ROOMS_BLOCK_REMOVE_BLOCK).set(PROFILE_ROOMS_BLOCK_REMOVE_BLOCK_NAME, context.rooms[i].title);
            roomsBlock[i].block(PROFILE_ROOMS_BLOCK_REMOVE_BLOCK).set(PROFILE_ROOMS_BLOCK_REMOVE_BLOCK_SRC, context.rooms[i].url);
        }
    }

    std::stringstream os;
    temp.render(os);
    profileHTML = os.str();
    return profileHTML;
}