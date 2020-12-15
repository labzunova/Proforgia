#ifndef PROFORGIA_SERVER_H
#define PROFORGIA_SERVER_H

#include <string>
#include <boost/log/trivial.hpp>

#include "connection/Connection.h"

typedef boost::system::error_code error_code;
class Server: boost::asio::noncopyable
{
public:
    explicit Server(const std::string& address, const std::string& port, std::shared_ptr<Connection_queue> loop );

    void start_server(); // Run the server's io_service loop.
    void stop_server();

private:
    void handle_accept( error_code e ); // принять новый коннект
    // Каждый раз, когда клиент подключается к серверу, вызывается handle_accept,
    // который начинает асинхронно читать от этого клиента, а так же асинхронно ждет нового клиента.

    void handle_stop();

    boost::asio::io_service io_service_; // очень важная штука для исполнения асинхронных операций
    boost::asio::ip::tcp::acceptor acceptor_; // акцептор (приемник) — один объект, который принимает клиентские подключения.
    std::shared_ptr<Connection_queue> connection_queue;
    std::shared_ptr<Connection> new_connection;
};

#endif //PROFORGIA_SERVER_H
