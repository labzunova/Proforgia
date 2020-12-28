#include <iostream>
#include "Server.h"
#include "Handler.h"
#include "Worker.cpp"

//typedef std::unordered_map<std::string, std::string> ContextMap;
//class TestHandler {
//public:
//    explicit TestHandler(ContextMap& context_): context(context_) {};
//    std::string get_response() {
//        return
//        "< HTTP/1.1 200 OK\n"
//        "< Date: Wed, 02 Dec 2020 15:14:34 GMT\n"
//        "< Server: WSGIServer/0.2 CPython/3.6.9\n"
//        "< Content-Type: text/html; charset=utf-8\n"
//        "< X-Frame-Options: DENY\n"
//        "< Content-Length: 160\n"
//        "< Vary: Cookie\n"
//        "< X-Content-Type-Options: nosniff\n"
//        "< Referrer-Policy: same-origin\n\n\n"
//        +context["path"];
//    }
//private:
//    ContextMap context;
//};

int main( int argc, char* argv[] ) {
  //  if ( argc != 2 )
  //      std::cout << "enter an address and port";
  //  else

    {
        std::shared_ptr<Connection_queue> queue = std::make_shared<Connection_queue>();
        Work<Connection_queue, Handler> work;
        work.start_work(queue);
        Server server("127.0.0.1", "5000", queue);
        // Server server( argv[0], argv[1], queue );
        server.start_server();
    }
    return 0;
}
