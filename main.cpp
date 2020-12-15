#include <iostream>
#include "Server.h"

int main( int argc, char* argv[] ) {
  //  if ( argc != 2 )
  //      std::cout << "enter an address and port";
  //  else
    {
        std::shared_ptr<Connection_queue> queue = std::make_shared<Connection_queue>();
        Server server("127.0.0.1", "5000", queue);
        // Server server( argv[0], argv[1], queue );
        server.start_server();
    }

    return 0;
}
