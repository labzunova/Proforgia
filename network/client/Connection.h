<<<<<<< HEAD
// single connection from a client
#ifndef PROFORGIA_CONNECTION_H
#define PROFORGIA_CONNECTION_H
#include <boost/asio.hpp>
//#include "boost/enable_shared_from_this.hpp"
//#include "Connection_loop.h"
#include "../request/Request.h"
#include "../reply/Reply.h"
#include "../parser/Parser.h"

class Connection_loop;

class Connection : public std::enable_shared_from_this<Connection> {
    public:
        explicit Connection( boost::asio::io_service& io_service,
                            Connection_loop& loop ); // создать коннект
        boost::asio::ip::tcp::socket& get_socket(); // вернуть сокет
        void start();  // стартовать первые асинхронные операции коннекта
        void stop();   // остановить всеасинхронные операции коннекта
    private:
        typedef boost::system::error_code error_code;
        void handle_read( const error_code& e,
                     std::size_t bytes_transferred );  // reading from socket and doing necessary operations
        void handle_write( const error_code& e ); // write in socket
        boost::asio::ip::tcp::socket socket_;
        Connection_loop& connection_loop; // The manager for this connection.

        // Для обработки входящего запроса request_handler& request_handler_; (не он, а строчка ниже)
        // API api; // тут будет объект класса логики сервера, который напишет Сережа

        std::array<char, 8192> buffer_; // Буфер для приходящих данных
       // Request request; // Прихдящий запрос
       // Reply reply; // ответ, который мы отправим обратно
};
typedef boost::shared_ptr<Connection> connection_ptr;


#endif //PROFORGIA_CONNECTION_H
=======
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
        explicit Connection( boost::asio::io_service& io_service,
                            Connection_manager& manager, API& api ); // создать коннект
        boost::asio::ip::tcp::socket& get_socket(); // вернуть сокет
        // void start();  // стартовать первые асинхронные операции коннекта - так было в примере буста
        // void stop();   // остановить всеасинхронные операции коннекта - так было в примере буста
    private:
        typedef boost::system::error_code error_code;
        void do_read( const error_code& e,
                     std::size_t bytes_transferred );  // reading from socket and doing necessary operations
        void do_write( const error_code& e ); // write in socket
        boost::asio::ip::tcp::socket socket_;
        Connection_manager& connection_manager; // The manager for this connection.

        // Для обработки входящего запроса request_handler& request_handler_; (не он, а строчка ниже)
        API api; // тут будет объект класса логики сервера, который напишет Сережа

        boost::array<char, 8192> buffer_; // Буфер для приходящих данных
        Request request; // Прихдящий запрос
        Reply reply; // ответ, который мы отправим обратно
};
typedef boost::shared_ptr<Connection> connection_ptr;


#endif //PROFORGIA_CONNECTION_H
>>>>>>> cascass improved
