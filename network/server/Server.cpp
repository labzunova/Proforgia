#include "Server.h"
#include <boost/asio.hpp>

void Server::start_server() {
// runserver
}

void Server::stop_server() {
// stop server
}

void Server::handle_accept(boost::shared_ptr<Connection> client, const Server::error_code &err) {
    // записыавем колиента в вектор клиентов
    // запускаем асинхронное чтение на нем

    // async_accept для нового клиента
    // (вызываю ожидание подключения нового клиента вроде как)
    // и тут же с помощью bind связываю с функцией handle_accept,
    // которая вызовется, когда он подключится
}

Server::Server(): service_(), acceptor_(service_) {

}
