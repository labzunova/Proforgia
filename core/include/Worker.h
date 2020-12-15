//
// Created by sergei on 28.11.2020.
//

#pragma once

#include <mutex>
#include <condition_variable>
#include <atomic>
#include <thread>
#include <memory>
#include <vector>
#include <boost/log/trivial.hpp>
#include <boost/lexical_cast.hpp>


template<class Queue, class Handler>
class Worker {
public:
    explicit Worker(std::shared_ptr<Queue> queue);
    ~Worker();

private:
    std::thread thr;
    std::shared_ptr<Queue> queue_;

    void run();
};

template<class Queue>
class Checker {
public:
    explicit Checker(std::shared_ptr<Queue> queue);
    ~Checker();

private:
    std::thread thr;
    std::shared_ptr<Queue> queue_;

    void run();
};


template<class Queue, class Handler>
class Work {
public:
    Work() = default;
    void start_work(std::shared_ptr<Queue> queue);
    void stop_work();

private:
    std::vector<std::shared_ptr<Worker<Queue, Handler>>> workers;
    std::shared_ptr<Checker<Queue>> checker;
};


