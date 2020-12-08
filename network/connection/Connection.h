#ifndef PROFORGIA_CONNECTION_H
#define PROFORGIA_CONNECTION_H

#include "connection_queue/Connection_queue.h"
#include "request/Request.h"

class Connection_queue;

class Connection : public std::enable_shared_from_this<Connection> {
    public:
        explicit Connection(boost::asio::io_service& io_service,
                            Connection_queue& loop );
        boost::asio::ip::tcp::socket& get_socket();
        void start();  // стартовать первые асинхронные операции коннекта
        void stop();   // остановить всеасинхронные операции коннекта
    private:
        typedef boost::system::error_code error_code;
        void handle_read( const error_code& e,
                     std::size_t bytes_transferred );  // reading from socket and doing necessary operations
        boost::asio::ip::tcp::socket socket_;
        Connection_queue& connection_queue;
        std::array<char, 8192> buffer_; // Буфер для приходящих данных
};
typedef boost::shared_ptr<Connection> connection_ptr;


#endif //PROFORGIA_CONNECTION_H
