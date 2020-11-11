#include "steps.h"
#include "BdManager.h"

Step::Status CheckLogin::Run(ContextStr& context) {
    BdManager bd_manager;
    if (!bd_manager.IsLoginUser(context.get("login")))
        return Status::FAILED;

    return Next(context);
}

Step::Status SessionSave::Run(ContextStr& context) {
    BdManager bd_manager;
    std::string login = context.get("login");
    std::string session = context.get("session");
    bd_manager.SetSession(login, session);

    return Next(context);
}

/// Проверка и получение прав пользователя
Step::Status CheckUser::Run(ContextStr& context) {
    std::string session = context.get("session");

    BdManager bd_manager;
    auto sessions = bd_manager.GetSession();
    for(auto & i : sessions)
        if(i == session)
            return Next(context);

    return Status::FAILED;
}

Step::Status RoomSave::Run(ContextStr& context) {
    BdManager bd_manager;

    BdManager::Room room;
    // TODO добавление данных в room из context

    bd_manager.AddRoom(room);

    return Next(context);
}

Step::Status UserUpdate::Run(ContextStr& context) {
    BdManager bd_manager;

    BdManager::User user;
    // TODO добавление данных в user из context

    bd_manager.UpdateUser(user);

    return Next(context);
}

Step::Status GetRoom::Run(ContextStr& context) {
    BdManager bd_manager;

    std::string room_id = context.get("room_id");
    BdManager::Room room = bd_manager.GetRoom(room_id);
    // TODO добавление данных в context из room

    return Next(context);
}

Step::Status GetUser::Run(ContextStr& context) {
    BdManager bd_manager;

    std::string user_id = context.get("user_id");
    BdManager::Room room = bd_manager.GetRoom(user_id);
    // TODO добавление данных в context из user

    return Next(context);
}

Step::Status DataSave::Run(ContextStr& context) {
    BdManager bd_manager;

    BdManager::Data data;
    // TODO добавление данных в data из context

    bd_manager.AddData(data);

    return Next(context);
}

Step::Status DataDelete::Run(ContextStr& context) {
    BdManager bd_manager;

    BdManager::Data data;
    // TODO добавление данных в data из context

    bd_manager.DeleteData(data);

    return Next(context);
}

Step::Status GetData::Run(ContextStr& context) {
    BdManager bd_manager;

    BdManager::Data data;
    // TODO добавление данных в data из context

    data = bd_manager.GetData(data);
    // TODO добавление данных в contest из data

    return Next(context);
}

Step::Status Deadline::Run(ContextStr& context) {
    BdManager bd_manager;
    std::string room_id = context.get("room_id");

    BdManager::Room room = bd_manager.GetRoom(room_id);
    // TODO добавление данных о дедлайнах в contest из room

    return Next(context);
}
