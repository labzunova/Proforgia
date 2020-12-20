#include <map>
#include "BaseTemplate.h"

BaseTemplate::BaseTemplate(Context& context) : context(context) {
}

std::vector<std::string> BaseTemplate::getCSS() {
    return std::vector<std::string>();
}

std::vector<std::string> BaseTemplate::getJS() {
    return std::vector<std::string>();
}

void BaseTemplate::setLoggedNavBar(Template& temp) const {
    auto& block_logged = temp.block(BASE_LOGGED_BLOCK);
    block_logged.set(BASE_LOGGED_BLOCK_USERNAME, context.user.username);
    block_logged.set(BASE_LOGGED_BLOCK_AVATAR, context.user.avatarUrl);
}

void BaseTemplate::setRightBlock(Template& temp) {
    temp.set(BASE_RIGHT_BLOCK_ROOM, context.currentRoom.url);
    auto& blockRight = temp.block(BASE_RIGHT_BLOCK);
    blockRight.repeat(context.tags.size());
    for (int i = 0; i < context.tags.size(); i++) {
        blockRight[i].set(BASE_RIGHT_BLOCK_TAG_NAME, context.tags[i].tag);
        blockRight[i].set(BASE_RIGHT_BLOCK_TAG_SRC, context.tags[i].url);
        blockRight[i].set(BASE_RIGHT_BLOCK_ROOM, context.currentRoom.url);
    }
}

void BaseTemplate::offLoggedNavBar(Template& temp) {
    auto& block_logged = temp.block(BASE_LOGGED_BLOCK);
    block_logged.disable();
}
