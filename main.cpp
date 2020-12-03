#include <iostream>
#include "Server.h"

int main() {
    Connection_loop loop;
    Server server("127.0.0.1", "5000", loop); // TODO: думаю так очередь не передают (мб сделать синглтон?...)
    server.start_server();
    return 0;
}