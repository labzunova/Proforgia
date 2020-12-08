#ifndef PROFORGIA_CONNECTION_QUEUE_H
#define PROFORGIA_CONNECTION_QUEUE_H

#include <utility>
#include <queue>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <mutex>

class Connection_queue: private boost::asio::noncopyable
{
public:
    struct Event { // событие, которое может по вызову callback записать данные в нужный сокет
        Event( std::map<std::string, std::string>&  data_, boost::asio::ip::tcp::socket& socket ): data(std::move( data_ )), socket_(  std::move(socket)  ) {} // TODO убрать magic numbers
        std::map<std::string, std::string> data;  // метод запроса, что нужно выполнить, необходимые данные, полученные из прасинга запроса
        void callback( std::string buffer )
        {
            boost::asio::async_write(socket_, boost::asio::buffer( buffer ),
                                     boost::bind( &Event::handle_write, this, boost::asio::placeholders::error) ); // TODO: почитать еще про bind
        }
    private:
        boost::asio::ip::tcp::socket socket_;
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
    std::mutex queue_mutex;
    void push_back( std::map<std::string, std::string>& data, boost::asio::ip::tcp::socket &socket_  ); // так кладутся задачи в очередь
    Event pop_front(); // для воркеров
    const int is_empty(); // для воркеров
    Connection_queue(Connection_queue *pQueue);

    Connection_queue();
};


#endif //PROFORGIA_CONNECTION_QUEUE_H
