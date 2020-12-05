#include <iostream>
#include "server/Server.h"

int main( int argc, char* argv[] ) {
  //  if ( argc != 2 )
  //      std::cout << "enter an address and port";
  //  else
    {
        Connection_queue queue;
        Server server("127.0.0.1", "5000", queue);
        // Server server( argv[0], argv[1], queue ); // TODO: думаю так очередь не передают (мб сделать синглтон?...)
        server.start_server();
    }

    return 0;
}