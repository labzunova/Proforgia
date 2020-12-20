#ifndef PROFORGIA_PROFILETEMPLATE_H
#define PROFORGIA_PROFILETEMPLATE_H

#include "NLTemplate.h"
#include "BaseTemplate.h"

#define PROFILE_WAY "../wt_templates/templates/profile.html"

#define PROFILE_ROOMS_BLOCK "rooms"
#define PROFILE_ROOMS_BLOCK_NAME "room_name"
#define PROFILE_ROOMS_BLOCK_SRC "room_src"
#define PROFILE_ROOMS_BLOCK_REMOVE_BLOCK "remove_room"
#define PROFILE_ROOMS_BLOCK_REMOVE_BLOCK_NAME "room_name"
#define PROFILE_ROOMS_BLOCK_REMOVE_BLOCK_SRC "room_src"

class ProfileTemplate : public BaseTemplate {
public:
    explicit ProfileTemplate(Context& context);

    std::string& getHTML() override;

private:
    std::string profileHTML;
};


#endif //PROFORGIA_PROFILETEMPLATE_H
