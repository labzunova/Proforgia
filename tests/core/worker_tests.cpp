//
// Created by sergei on 02.12.2020.
//

#include "gtest/gtest.h"
#include <string>
#include <queue>
#include <utility>
#include <iostream>

//#include "Worker.cpp"
#include "Handler.h"

typedef std::map<std::string, std::string> Context;

struct Request {
    explicit Request(Context context) : context(std::move(context)) {};
    static void call_back(const std::string& string) {
        std::cout << "done work" << std::endl;
    };

    Context context;
};

typedef std::queue<Request> Queue;

class MockHandler {
public:
    explicit MockHandler(Context&) {};
    std::string get_response() {
        sleep(1);
        return "response";
    }
};

TEST(WorkerTests, TimeWork) {
    Context context = {{"method", "GET"},
                     {"action", "MAIN"}};
    Handler h(context);
    h.get_respons();

}

//
//TEST(WorkerTests, TimeWork){
//
//    Context context = {{"method", "GET"},
//                       {"action", "MAIN"}};
//    auto queue = std::make_shared<Queue>();
//
//    queue->push(Request(context));
//    queue->push(Request(context));
//    queue->push(Request(context));
//    queue->push(Request(context));
//
//    clock_t t = clock();
//
//    Work<Queue, MockHandler> work;
//    work.start_work(queue);
//    while(!queue->empty()) sleep(1);
//    work.stop_work();
//
//    const double work_time = (clock() - t) / double(CLOCKS_PER_SEC);
//
//    ASSERT_TRUE(queue->empty());
//
//    ASSERT_TRUE(work_time <= 2);
//}
