#include <iostream>
#include "server/Server.h"
#include "include/Worker.h"


typedef std::map<std::string, std::string> Context;
class MockHandler {
public:
    explicit MockHandler(Context&) {};
    std::string get_response() {
        sleep(1);
        return "response";
    }
};

int main( int argc, char* argv[] ) {
  //  if ( argc != 2 )
  //      std::cout << "enter an address and port";
  //  else
    {
        Connection_queue queue;
        Server server("127.0.0.1", "5000", queue);
        // Server server( argv[0], argv[1], queue ); // TODO: думаю так очередь не передают (мб сделать синглтон?...)
        Work<Connection_queue, MockHandler> work;
        work.start_work(std::make_shared<Connection_queue>(&queue));
        server.start_server();
    }

    return 0;
}