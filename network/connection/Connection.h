// single connection from a connection
#ifndef PROFORGIA_CONNECTION_H
#define PROFORGIA_CONNECTION_H
#include <boost/asio.hpp>
#include "../request/Request.h"
#include "../reply/Reply.h"
#include "../parser/Parser.h"

class Connection_loop;

class Connection : public std::enable_shared_from_this<Connection> {
    public:
        explicit Connection( boost::asio::io_service& io_service,
                            Connection_loop& loop );
        boost::asio::ip::tcp::socket& get_socket();
        void start();  // стартовать первые асинхронные операции коннекта
        void stop();   // остановить всеасинхронные операции коннекта
    private:
        typedef boost::system::error_code error_code;
        void handle_read( const error_code& e,
                     std::size_t bytes_transferred );  // reading from socket and doing necessary operations
        void handle_write( const error_code& e ); // write in socket
        boost::asio::ip::tcp::socket socket_;
        Connection_loop& connection_loop;

        // Для обработки входящего запроса request_handler& request_handler_;

        std::array<char, 8192> buffer_; // Буфер для приходящих данных
       // Request request; // Прихдящий запрос
       // Reply reply; // ответ, который мы отправим обратно
};
typedef boost::shared_ptr<Connection> connection_ptr;


#endif //PROFORGIA_CONNECTION_H
