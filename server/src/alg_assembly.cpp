#include "alg_assembly.h"

void Assembly::InstallDependency(std::vector<Step *> steps) {
    for(int i = 0; i < steps.size() - 1; i++)
        steps[i]->SetNext(steps[i + 1]);
}

Step* Assembly::GetAuth() {
    std::vector<Step*> steps;
    steps.push_back(new Hash);
    steps.push_back(new CheckLogin);
    steps.push_back(new GenSession);
    steps.push_back(new SessionSave);

    InstallDependency(steps);

    return steps[0];
}

Step *Assembly::GetCreatorRoom() {
    std::vector<Step*> steps;
    steps.push_back(new CheckUser);
    steps.push_back(new RoomPrep);
    steps.push_back(new RoomSave);
    steps.push_back(new UserUpdate);

    InstallDependency(steps);

    return steps[0];
}

Step *Assembly::GetInfoRoom() {
    std::vector<Step*> steps;
    steps.push_back(new CheckUser);
    steps.push_back(new GetRoom);
    steps.push_back(new CreateView);

    InstallDependency(steps);

    return steps[0];
}

Step *Assembly::AddInfoRoom() {
    std::vector<Step*> steps;
    steps.push_back(new CheckUser);
    steps.push_back(new DataSave);

    InstallDependency(steps);

    return steps[0];
}

Step *Assembly::DelInfoRoom() {
    std::vector<Step*> steps;
    steps.push_back(new CheckUser);
    steps.push_back(new DataDelete);

    InstallDependency(steps);

    return steps[0];
}

Step *Assembly::GetInfoUser() {
    std::vector<Step*> steps;
    steps.push_back(new GetUser);
    steps.push_back(new CreateView);

    InstallDependency(steps);

    return steps[0];
}

Step *Assembly::AddFavoritesUser() {
    std::vector<Step*> steps;
    steps.push_back(new CheckUser);
    steps.push_back(new GetRoom);
    steps.push_back(new UserUpdate);

    InstallDependency(steps);

    return steps[0];
}

Step *Assembly::GetFavoritesUser() {
    std::vector<Step*> steps;
    steps.push_back(new CheckUser);
    steps.push_back(new GetUser);
    steps.push_back(new CreateView);

    InstallDependency(steps);

    return steps[0];
}

Step *Assembly::DeleteFavoritesUser() {
    std::vector<Step*> steps;
    steps.push_back(new CheckUser);
    steps.push_back(new DataDelete);

    InstallDependency(steps);

    return steps[0];
}

Step *Assembly::GetLastData() {
    std::vector<Step*> steps;
    steps.push_back(new CheckUser);
    steps.push_back(new GetData);
    steps.push_back(new CreateView);

    InstallDependency(steps);

    return steps[0];
}

Step *Assembly::GetDeadline() {
    std::vector<Step*> steps;
    steps.push_back(new CheckUser);
    steps.push_back(new Deadline);
    steps.push_back(new CreateView);

    InstallDependency(steps);

    return steps[0];
}

Step *Assembly::GetPopularData() {
    std::vector<Step*> steps;
    steps.push_back(new CheckUser);
    steps.push_back(new GetData);
    steps.push_back(new SortPopularData);
    steps.push_back(new CreateView);

    InstallDependency(steps);

    return steps[0];
}
