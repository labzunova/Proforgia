#ifndef PROFORGIA_SERVER_H
#define PROFORGIA_SERVER_H
#include <boost/asio.hpp>
#include <string>
#include "../client/Connection.h"
# include "../connection_manager/Connection_manager.h"

typedef boost::system::error_code error_code;
class Server: boost::asio::noncopyable
{
public:
    explicit Server( const std::string& address, const std::string& port ); // создает сервер чтобы слушать конкретный
                    // адрес и порт, ну и TODO: в примере boost тут была еще какая-то директория

    void start_server(); // Run the server's io_service loop.
    void stop_server(); // Остановить сервер

private:
    void handle_accept( error_code& e ); // принять новый коннект
    // Каждый раз, когда клиент подключается к серверу, вызывается handle_accept,
    // который начинает асинхронно читать от этого клиента, а так же асинхронно ждет нового клиента.

    /// Handle a request to stop the server. ???????????????????
    void handle_stop(); // TODO: не поняла зачем это и stop_server

    boost::asio::io_service io_service_; // очень важная штука для исполнения асинхронных операций
    boost::asio::ip::tcp::acceptor acceptor_; // акцептор (приемник) — один объект, который принимает клиентские подключения.
    Connection_manager connection_manager; // менеджер для всех коннектов, содержащий вектор коннектов
    connection_ptr new_connection; // The next connection to be accepted.
    API api; // исполнитель для всех запросов - API Серёжи
};

#endif //PROFORGIA_SERVER_H
