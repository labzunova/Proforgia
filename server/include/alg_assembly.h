#pragma once

#include "steps.h"
#include <vector>

class Assembly {
public:
    Assembly() = default;

    Step* GetAuth();
    Step* GetCreatorRoom();
    static Step* GetInfoRoom();
    static Step* AddInfoRoom();
    static Step* DelInfoRoom();
    static Step* GetInfoUser();
    static Step* AddFavoritesUser();
    static Step* GetFavoritesUser();
    static Step* DeleteFavoritesUser();
    static Step* GetLastData();
    static Step* GetDeadline();
    static Step* GetPopularData();

private:
    static void InstallDependency(std::vector<Step*>);
};
