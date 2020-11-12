#pragma once

#include "UserApi.h"
#include "entities/File.h"
#include "entities/User.h"
#include "entities/Room.h"

class CustomerApi : public UserApi {
public:
    CustomerApi(User user, View view)
    : UserApi(view)
    , user_(user){};

    std::string GetMainPage();
    std::string GetRoomPage(int id_room);
    std::string GetRoomPage(int id_room, Location location);
    int PostFile(int id_room, Location location, File::Data &data);
    std::string GetFile(int id_room, Location location);

protected:
    User user_;
};
