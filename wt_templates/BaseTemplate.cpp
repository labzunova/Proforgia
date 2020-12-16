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
    auto& block_logged = temp.block("logged_block");
    block_logged.set("username", context.user.username);
    block_logged.set("avatar_res", context.user.avatarUrl);
}

void BaseTemplate::setRightBlock(Template& temp) {
    auto& blockRight = temp.block("right_block.tags");
    blockRight.repeat(context.tags.size());
    for (int i = 0; i < context.tags.size(); i++) {
        blockRight[i].set("tag", context.tags[i].tag);
        blockRight[i].set("tag.url", context.tags[i].url);
    }
}

void BaseTemplate::offLoggedNavBar(Template& temp) {
    auto& block_logged = temp.block("logged_block");
    block_logged.disable();
}
