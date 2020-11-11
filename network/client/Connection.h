// aka client
#ifndef PROFORGIA_CONNECTION_H
#define PROFORGIA_CONNECTION_H
#include <boost/asio.hpp>
#define BOFFER 1024

class Connection: std::enable_shared_from_this<Connection>, boost::asio::noncopyable
{
    public:
        typedef boost::system::error_code error_code;
        typedef boost::shared_ptr<Connection> ptr;
        Connection(boost::asio::io_service& io): socket_(io) {}
        ~Connection() {};
        void do_read();  // reading from socket and doing necessary operations
        void do_write( const std::string & msg ); // write in socket
        void start_client(); // async connect to server
        void stop_client(); // socket closing
    private:
        boost::asio::ip::tcp::socket socket_;
        boost::asio::ip::tcp::endpoint ep;
        char buffer[BOFFER];
        // TODO: deadline_timer to ping checking
        //API api - тут будет объект класса логики сервера, который напишет Сережа
};

#endif //PROFORGIA_CONNECTION_H
