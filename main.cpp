#include <iostream>
#include "Server.h"

int main() {
    Server server("127.0.0.1", "5000");
    server.start_server();
    return 0;
}