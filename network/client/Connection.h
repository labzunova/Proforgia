// single connection from a client
#ifndef PROFORGIA_CONNECTION_H
#define PROFORGIA_CONNECTION_H
#include <boost/asio.hpp>
#include "../connection_manager/Connection_manager.h"
#include "../request/Request.h"
#include "../reply/Reply.h"
#include "../parser/Parser.h"
#define BOFFER 1024

class Connection: std::enable_shared_from_this<Connection>, boost::asio::noncopyable
{
    public:
        explicit Connection(boost::asio::io_context& io_context,
                            Connection_manager& manager, API& api); // construct a connection with io_context
        // boost::asio::ip::tcp::socket& socket_(); // why & ???
        void start();  // Start the first asynchronous operation for the connection.
        void stop();   // Stop all asynchronous operations associated with the connection.
    private:
        typedef boost::system::error_code error_code;
        void do_read(const error_code& e,
                     std::size_t bytes_transferred);  // reading from socket and doing necessary operations
        void do_write(const error_code& e); // write in socket
        boost::asio::ip::tcp::socket socket_;
        Connection_manager& connection_manager; // The manager for this connection.

        // Для обработки входящего запроса request_handler& request_handler_;
        ///API api - тут будет объект класса логики сервера, который напишет Сережа

        boost::array<char, 8192> buffer_; // Буфер для приходящих данных
        Request request; // Прихдящий запрос
        Reply reply; // ответ, который мы отправим обратно
        Parser parser; // Парсер для приходящего запроса
};
typedef boost::shared_ptr<Connection> ptr;


#endif //PROFORGIA_CONNECTION_H
