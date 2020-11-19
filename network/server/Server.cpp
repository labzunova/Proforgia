#include "Server.h"
#include <boost/asio.hpp>

Server::Server( const std::string &address, const std::string &port ):
    io_service_(),
    acceptor_()( io_service_ ),
    connection_manager(),
    new_connection_( new Connection( io_service_, connection_manager, api ) ),
    api()
{
    // даем акцептору нужну информацию и запускаем async_accept
}

void Server::start_server()
{
    // run server (run io_service)
}

void Server::stop_server()
{
    // Post a call to the stop function so that server::stop() is safe to call
    // from any thread.
    io_service_.post(boost::bind(&Server::handle_stop, this)); // TODO: разобраться, почему так
}

void Server::handle_accept( error_code &err )
{
    // запускаем connection_manager,
    // записыавем колиента в вектор клиентов

    // async_accept для нового клиента
    // (вызываю ожидание подключения нового клиента вроде как)
    // и тут же с помощью bind связываю с функцией handle_accept,
    // которая вызовется, когда он подключится
}

void Server::handle_stop() {
    // биндится
    // The server is stopped by cancelling all outstanding asynchronous
    // operations. Once all operations have finished the io_service::run() call
    // will exit.
    acceptor_.close();
    connection_manager.stop_all();
}
