#include <iostream>
#include "server/Server.h"
#include "src/Worker.cpp"


typedef std::map<std::string, std::string> Context;
class MockHandler {
public:
    explicit MockHandler(Context&) {};
    std::string get_response() {
        return "< HTTP/1.1 200 OK\n"
               "< Date: Tue, 08 Dec 2020 10:22:27 GMT\n"
               "< Server: WSGIServer/0.2 CPython/3.6.9\n"
               "< Content-Type: text/html; charset=utf-8\n"
               "< X-Frame-Options: DENY\n"
               "< Content-Length: 193\n"
               "< Vary: Cookie\n"
               "< X-Content-Type-Options: nosniff\n"
               "< Referrer-Policy: same-origin\n"
               "< \n"
               "\n"
               "\n"
               "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\" \"http://www.w3.org/TR/html4/strict.dtd\">\n"
               "<html>\n"
               " <head>\n"
               "  <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n"
               "  <title>Пример веб-страницы</title>\n"
               " </head>\n"
               " <body>\n"
               "  <h1>Заголовок</h1>\n"
               "  <!-- Комментарий -->\n"
               "  <p>Первый абзац.</p>\n"
               "  <p>Второй абзац.</p>\n"
               " </body>\n"
               "</html>";

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