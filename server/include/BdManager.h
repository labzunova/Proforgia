#pragma once

#include <string>
#include <vector>

class BdManager {
public:

    struct Data {
        /// необходимые для сохраниения данные
    };

    struct User {
        std::string name;
        std::string last_name;
        std::string id;
        std::string password;
    };

    struct Room {
        std::string login_admin_user;
        std::vector<std::string> login_user;
        std::string room_id;
        std::string name_room;
    };


public:
    bool IsLoginUser(std::string login_user);
    bool IsPassword(std::string login_user);
    void SetSession(std::string login_user, std::string session);
    bool AddUser(User user);
    bool UpdateUser(User user);
    bool ConnectRoom(std::string login_user, std::string id_room); // присоединение пользователя к комнате

    bool AddRoom(Room room);
    Room GetRoom(std::string id_room);
    void AddData(Data data);
    void DeleteData(Data data);
    Data GetData(Data data);
    std::vector<std::string> GetSession();
};
