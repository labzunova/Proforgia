#include "CustomerApi.h"

std::string CustomerApi::GetMainPage() {
    Context context;
    // TODO конвентируем данные в Context
    view_.SetPage(View::MAIN);
    return view_.Render(context);
}

std::string CustomerApi::GetRoomPage(int id_room) {
    Context context;
    // TODO получаем комнату по юзеру
    // TODO конвентируем данные комнаты и юзера в Context
    view_.SetPage(View::ROOM);
    return view_.Render(context);
}

std::string CustomerApi::GetRoomPage(int id_room, Location location) {
    Context context;
    // TODO получаем комнату и странуцу в ней
    // TODO конвентируем данные комнаты и юзера в Context
    view_.SetPage(View::ROOM);
    return view_.Render(context);
}

std::string CustomerApi::GetFile(int id_room, Location location) {
    Context context;
    File file(user_.getId());
    file.Fill();
    // TODO конвентируем данные файла и юзера в контекст
    view_.SetPage(View::FILE);
    return view_.Render(context);
}

int CustomerApi::PostFile(int id_room, Location location, File::Data &data) {
    Context context;
    // TODO находим файл в комнте
    File file(location);
    Room room(id_room);
    room.AddFile(file);

    return 0;
}
