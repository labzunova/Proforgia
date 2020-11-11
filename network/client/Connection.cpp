#include "Connection.h"
#include "../parser/Parser.h"
#include <boost/asio.hpp>

void Connection::do_read() {
 // читаем, отправляем на обработку в API
 // вызываем do_write чтобы записать ответ
}

void Connection::do_write(const std::string &msg) {
 // запись ответа в сокет
}

void Connection::start_client() {
 // запуск асинхронного чтения
}

void Connection::stop_client() {
 // закрытие коннекта если что-то пошло не так
}
