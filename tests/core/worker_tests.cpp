//
// Created by sergei on 02.12.2020.
//

#include "gtest/gtest.h"
#include <string>
#include <queue>
#include <iostream>

#include "Worker.cpp"

typedef std::map<std::string, std::string> Context;


class TestHandler {
public:
    explicit TestHandler(Context&) {};
    std::string get_response() {
        sleep(1);
        return "response";
    }
};

class TestQueue {
public:
    struct Event {
        explicit Event(Context& ctx) : data(ctx) {}

        Context data;
        void callback( std::string buffer ) {
            std::cout << "done work\n";
        }
    };

    Event pop_front() {
        auto ev = q.front();
        q.pop();
        return ev;
    };
    void push_back(Event& ev) {
        q.push(ev);
    };
    bool is_empty() {
        return q.empty();
    };

private:
    std::queue<Event> q;
};


TEST(WorkerTests, TimeWork){

    Context context = {{"method", "GET"},
                       {"action", "MAIN"}};
    TestQueue::Event event(context);
    auto queue = std::make_shared<TestQueue>();


    queue->push_back(event);
    queue->push_back(event);
    queue->push_back(event);
    queue->push_back(event);

    clock_t t = clock();

    Work<TestQueue, TestHandler> work;
    work.start_work(queue);
    while(!queue->is_empty()) sleep(1);
    work.stop_work();

    const double work_time = (clock() - t) / double(CLOCKS_PER_SEC);

    ASSERT_TRUE(queue->is_empty());

    ASSERT_TRUE(work_time <= 2);
}
