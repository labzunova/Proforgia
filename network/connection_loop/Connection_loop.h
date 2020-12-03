#ifndef PROFORGIA_CONNECTION_LOOP_H
#define PROFORGIA_CONNECTION_LOOP_H
#include <utility>
#include <queue>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

class Connection_loop: private boost::asio::noncopyable
{
private:
    struct Event { // событие, которое может по вызову callback записать данные в нужный сокет
        Event( std::map<std::string, std::string> data_, boost::asio::ip::tcp::socket sockett ): data( std::move( data_ ) ), socket_(  sockett  ) {} // TODO убрать magic numbers
        std::map<std::string, std::string> data;  // метод запроса, что нужно выполнить, необходимые данные, полученные из прасинга запроса
        void callback( std::array<char, 8192> buffer ) {
            boost::asio::async_write(socket_, boost::asio::buffer( buffer ),
                                     boost::bind( &Event::handle_write, boost::asio::placeholders::error ) ); // убрала shared_from_this - не компилится. TODO: понять как
        }
    private:
        boost::asio::ip::tcp::socket &socket_;
        void handle_write( const boost::system::error_code &e )
        {
            // выполняющаяся при чтении функция, которая биндится при запуске асинхронного чтения
            if (!e)
            {
                // Initiate graceful connection closure.
                boost::system::error_code ignored_ec;
                socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
            }
        }
    };
    std::queue<Event> connections;
public:
    void push_back( std::map<std::string, std::string> data, boost::asio::ip::tcp::socket &socket_  ); // так кладутся задачи в очередь
    Event pop_front(); // для воркеров
    int is_empty(); // для воркеров
};


#endif //PROFORGIA_CONNECTION_LOOP_H
