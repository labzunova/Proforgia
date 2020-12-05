//
// Created by sergei on 28.11.2020.
//

#pragma once

#include <queue>
#include <string>
#include <map>
#include <mutex>
#include <condition_variable>
#include <atomic>

static std::mutex mtx;
static std::condition_variable cv;
static std::atomic<bool> is_work;

template<class Queue, class Handler>
class Worker {
public:
    static std::string start_work(Queue& queue);
    static void stop_work();

private:
    static void worker(Queue& queue);
    static void checker(Queue& queue);
};
