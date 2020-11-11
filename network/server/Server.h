#ifndef PROFORGIA_SERVER_H
#define PROFORGIA_SERVER_H
#include <boost/asio.hpp>
#include "../client/Connection.h"

class Server: std::enable_shared_from_this<Server>, boost::asio::noncopyable
{
    public:
        typedef boost::system::error_code error_code;
        typedef boost::shared_ptr<Server> ptr;
        std::vector<ptr> clients; // array of clients for async working
        Server();
        void start_server();
        void stop_server();
    private:
        boost::shared_ptr<Connection> connection_;
        void handle_accept(boost::shared_ptr<Server> client,  const error_code & err); // accepting clients
        // Каждый раз, когда клиент подключается к серверу, вызывается handle_accept,
        // который начинает асинхронно читать от этого клиента, а так же асинхронно ждет нового клиента.
        boost::asio::io_service service_; // очень важное непонятно что
        boost::asio::ip::tcp::acceptor acceptor_; // акцептор (приемник) — один объект, который принимает клиентские подключения.
        boost::asio::ip::tcp::socket socket_;
};

#endif //PROFORGIA_SERVER_H
