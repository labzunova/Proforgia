//
// Created by sergei on 28.11.2020.
//

#include "Worker.h"
#include "Handler.h"

void Worker::start_work() {
    // TODO создание разных потоков
    worker();

    checker();
}

void Worker::worker() {
    ///
    auto request = queue_.front();
    queue_.pop();
    Handler handler(request.context);
    request.call_back(handler.start_process());
    ///
}

void Worker::checker() {
    // TODO когда очередь не пуста будит worker
}
