//
// Created by sergei on 28.11.2020.
//

#include "Worker.h"

static std::mutex mtx;
static std::condition_variable cv;
static std::atomic<bool> exit_flag;


template<class Queue, class Handler>
void Work<Queue, Handler>::start_work(std::shared_ptr<Queue> queue) {
    exit_flag = false;
    unsigned int max_thread = std::thread::hardware_concurrency();
    for(int i = 0; i < max_thread - 1; i++) {
        workers.push_back(std::make_shared<Worker<Queue, Handler>>(queue));
    }
    checker = std::make_shared<Checker<Queue>>(queue);
}

template<class Queue, class Handler>
void Work<Queue, Handler>::stop_work() {
    exit_flag = true;
    cv.notify_all();
}

template<class Queue, class Handler>
Worker<Queue, Handler>::Worker(std::shared_ptr<Queue> queue)
    : queue_(queue)
    , thr(&Worker::run, this){}


template<class Queue, class Handler>
Worker<Queue, Handler>::~Worker() {
    thr.join();
}

template<class Queue, class Handler>
void Worker<Queue, Handler>::run() {
    BOOST_LOG_TRIVIAL(info) << ("Create worker: " + boost::lexical_cast<std::string>(std::this_thread::get_id()));

    typename Queue::Event * request;
    while (!exit_flag) {
        {
            std::unique_lock<std::mutex> locker(mtx);
            cv.wait(locker);


            if (exit_flag)
                break;

            if (queue_->is_empty())
                continue;

            request = new typename Queue::Event(queue_->pop_front());
        }

//        context = {{"method", "GET"},    // релиз
//                           {"action", "MAIN"}};    // релиз
        Handler handler(request->data);   // релиз
//        std::map<std::string, std::string> ctx = {{"method", "GET"}, {"action", "MAIN"}};     // для тестов
//        Handler handler(ctx);   // для тестов
        request->callback(handler.get_response());
    }
    BOOST_LOG_TRIVIAL(info) << ("Delete worker: " + boost::lexical_cast<std::string>(std::this_thread::get_id()));
}



template<class Queue>
Checker<Queue>::Checker(std::shared_ptr<Queue> queue)
    : queue_(queue)
    , thr(&Checker::run, this){}

template<class Queue>
Checker<Queue>::~Checker() {
    thr.join();
}

template<class Queue>
void Checker<Queue>::run() {
    BOOST_LOG_TRIVIAL(info) << ("Create checker: " + boost::lexical_cast<std::string>(std::this_thread::get_id()));
    while(!exit_flag) {
        std::unique_lock<std::mutex> locker(mtx);
        if(!queue_->is_empty())
        {
            cv.notify_one();
        }
    }
    BOOST_LOG_TRIVIAL(info) << ("Delete checker: " + boost::lexical_cast<std::string>(std::this_thread::get_id()));
}

