#pragma once

#include "alg_assembly.h"
#include <string>

class Server {
public:

    struct Data {
    };

public:
    Server() { assembly = new Assembly; }
    Server(Server &) = delete;
    ~Server() { delete assembly; }

    Context<>::ObjectView Authorize(const Data& data);
    Context<>::ObjectView Register(const Data& data);
    void CreateRoom(const Data& data);
    Context<>::ObjectView GetInfoRoom(const Data& data);
    void AddInfoRoom(const Data& data);
    void DelInfoRoom(const Data& data);
    Context<>::ObjectView GetInfoUser(const Data& data);
    void AddFavoritesUser(const Data& data);
    Context<>::ObjectView GetFavoritesUser(const Data& data);
    void DeleteFavoritesUser(const Data& data);
    Context<>::ObjectView GetLastData(const Data& data);
    Context<>::ObjectView GetDeadline(const Data& data);
    Context<>::ObjectView GetPopularData(const Data& data);

private:
    Assembly* assembly;
};
