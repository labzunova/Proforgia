#include "Connection.h"
#include "../parser/Parser.h"
#include <boost/asio.hpp>

Connection::Connection(boost::asio::io_context &io_context, Connection_manager &manager, API &api) {

}

void Connection::start() {

}

void Connection::stop() {

}
void Connection::do_read(const Connection::error_code &e, std::size_t bytes_transferred) {

}

void Connection::do_write(const Connection::error_code &e) {

}

