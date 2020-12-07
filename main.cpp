#include <iostream>
#include "server/Server.h"
#include "src/Worker.cpp"


typedef std::map<std::string, std::string> Context;
class MockHandler {
public:
    explicit MockHandler(Context&) {};
    std::string get_response() {
        return "response";
    }
};

int main( int argc, char* argv[] ) {
  //  if ( argc != 2 )
  //      std::cout << "enter an address and port";
  //  else
    {
        std::shared_ptr<Connection_queue> queue = std::make_shared<Connection_queue>();
        Server server("127.0.0.1", "5000", *queue);
        // Server server( argv[0], argv[1], queue ); // TODO: думаю так очередь не передают (мб сделать синглтон?...)
        Work<Connection_queue, MockHandler> work;
        work.start_work(queue);
        server.start_server();
    }

    return 0;
}