//
// Created by sergei on 28.11.2020.
//

#include "Worker.h"

#include <thread>
#include <boost/log/trivial.hpp>
#include <boost/lexical_cast.hpp>

template<class Queue, class Handler>
std::string Worker<Queue, Handler>::start_work(Queue& queue) {
    is_work.store(true);

    for(int i = 0; i < std::thread::hardware_concurrency() - 1; i++) {
        std::thread thread(worker, std::ref(queue));

        thread.detach();
    }

    std::thread thread(checker, std::ref(queue));
    thread.detach();

    return "starting";
}

template<class Queue, class Handler>
void Worker<Queue, Handler>::worker(Queue& queue) {
    BOOST_LOG_TRIVIAL(info) << ("Create worker: " + boost::lexical_cast<std::string>(std::this_thread::get_id()));
    while(is_work.load()) {
        std::unique_lock<std::mutex> locker(mtx);
        cv.wait(locker);

        if(queue.empty())
            continue;

        auto request = queue.front();
        queue.pop();
        Handler handler(request.context);
        request.call_back(handler.get_response());
    }
    BOOST_LOG_TRIVIAL(info) << ("Delete worker: " + boost::lexical_cast<std::string>(std::this_thread::get_id()));
}

template<class Queue, class Handler>
void Worker<Queue, Handler>::checker(Queue& queue) {
    BOOST_LOG_TRIVIAL(info) << ("Create checker: " + boost::lexical_cast<std::string>(std::this_thread::get_id()));
    while(is_work.load()) {
        std::unique_lock<std::mutex> locker(mtx);
        if(!queue.empty())
            cv.notify_one();
    }
    cv.notify_all();
    BOOST_LOG_TRIVIAL(info) << ("Delete checker: " + boost::lexical_cast<std::string>(std::this_thread::get_id()));
}

template<class Queue, class Handler>
void Worker<Queue, Handler>::stop_work() {
    is_work.store(false);
    std::unique_lock<std::mutex> locker(mtx);
}
