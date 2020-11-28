#include "Server.h"
#include <boost/asio.hpp>
#include "boost/bind.hpp"

Server::Server( const std::string &address, const std::string &port ):
    io_service_(),
    acceptor_( io_service_ ),
    connection_loop(),
    new_connection( new Connection( io_service_, connection_loop ) )
{
    boost::asio::ip::tcp::resolver resolver(io_service_);
    boost::asio::ip::tcp::resolver::query query( address, port );
    boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
    acceptor_.open( endpoint.protocol() );
    acceptor_.set_option( boost::asio::ip::tcp::acceptor::reuse_address( true ) );
    acceptor_.bind( endpoint );
    acceptor_.listen();
    acceptor_.async_accept( new_connection->get_socket(),
                           boost::bind(&Server::handle_accept, this,
                                       boost::asio::placeholders::error ) );
    // даем акцептору нужну информацию и запускаем async_accept
}

void Server::start_server()
{
    io_service_.run();
}

void Server::stop_server()
{
    // Post a call to the stop function so that server::stop() is safe to call
    // from any thread.
    io_service_.post(boost::bind(&Server::handle_stop, this)); // TODO: разобраться, почему так
}

void Server::handle_accept( error_code &err )
{
    if ( !err )
    {
        // запускаем connection_loop,
        // записыавем колиента в вектор клиентов
        connection_loop.start(new_connection);
        new_connection.reset(new Connection(io_service_,
                                             connection_loop));
        // async_accept для нового клиента
        // (вызываю ожидание подключения нового клиента вроде как)
        // и тут же с помощью bind связываю с функцией handle_accept,
        // которая вызовется, когда он подключится
        acceptor_.async_accept(new_connection->get_socket(),
                               boost::bind(&Server::handle_accept, this,
                                           boost::asio::placeholders::error));
    }
}

void Server::handle_stop() {
    // биндится
    // The server is stopped by cancelling all outstanding asynchronous
    // operations. Once all operations have finished the io_service::run() call
    // will exit.
    acceptor_.close();
    connection_loop.stop_all();
}