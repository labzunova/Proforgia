#include "Server.h"
#include "Context.h"

Context<>::ObjectView Server::Register(const Server::Data& data) {

}

Context<>::ObjectView Server::Authorize(const Server::Data &data) {
    Context<std::string, std::string> context;
    // TODO заполняем контекст пришедшими данными
    Step::Status status = assembly->GetAuth()->Run(context);

    return context.GetView();
}

void Server::CreateRoom(const Server::Data &data) {
    Context<std::string, std::string> context;
    // TODO заполняем контекст пришедшими данными
    assembly->GetCreatorRoom()->Run(context);
}

Context<>::ObjectView Server::GetInfoRoom(const Server::Data &data) {
    Context<std::string, std::string> context;
    // TODO заполняем контекст пришедшими данными
    Step::Status status = assembly->GetInfoRoom()->Run(context);

    return context.GetView();
}

void Server::AddInfoRoom(const Server::Data &data) {
    Context<std::string, std::string> context;
    // TODO заполняем контекст пришедшими данными
    assembly->GetInfoRoom()->Run(context);
}

void Server::DelInfoRoom(const Server::Data &data) {
    Context<std::string, std::string> context;
    // TODO заполняем контекст пришедшими данными
    assembly->DelInfoRoom()->Run(context);
}

Context<>::ObjectView Server::GetInfoUser(const Server::Data &data) {
    Context<std::string, std::string> context;
    // TODO заполняем контекст пришедшими данными
    Step::Status status = assembly->GetInfoUser()->Run(context);

    return context.GetView();
}

void Server::AddFavoritesUser(const Server::Data &data) {
    Context<std::string, std::string> context;
    // TODO заполняем контекст пришедшими данными
    assembly->AddFavoritesUser()->Run(context);
}

Context<>::ObjectView Server::GetFavoritesUser(const Server::Data &data) {
    Context<std::string, std::string> context;
    // TODO заполняем контекст пришедшими данными
    Step::Status status = assembly->GetFavoritesUser()->Run(context);

    return context.GetView();
}

void Server::DeleteFavoritesUser(const Server::Data &data) {
    Context<std::string, std::string> context;
    // TODO заполняем контекст пришедшими данными
    assembly->DeleteFavoritesUser()->Run(context);
}

Context<>::ObjectView Server::GetLastData(const Server::Data &data) {
    Context<std::string, std::string> context;
    // TODO заполняем контекст пришедшими данными
    Step::Status status = assembly->GetLastData()->Run(context);

    return context.GetView();
}

Context<>::ObjectView Server::GetDeadline(const Server::Data &data) {
    Context<std::string, std::string> context;
    // TODO заполняем контекст пришедшими данными
    Step::Status status = assembly->GetDeadline()->Run(context);

    return context.GetView();
}

Context<>::ObjectView Server::GetPopularData(const Server::Data &data) {
    Context<std::string, std::string> context;
    // TODO заполняем контекст пришедшими данными
    Step::Status status = assembly->GetPopularData()->Run(context);

    return context.GetView();
}
