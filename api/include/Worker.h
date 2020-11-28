//
// Created by sergei on 28.11.2020.
//

#pragma once

#include <queue>
#include <string>
#include <map>
#include <mutex>
#include <condition_variable>

struct Request {
    void call_back(const std::string&) {};

    std::map<std::string, std::string> context;
};


typedef std::queue<Request> Queue;
class Worker {
public:
    explicit Worker(Queue& queue) : queue_(queue) {};
    void start_work();

private:
    void worker();
    void checker();

private:
    Queue queue_;
    std::mutex mtx;
    std::condition_variable cv;
};
