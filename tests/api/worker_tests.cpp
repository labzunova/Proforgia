//
// Created by sergei on 02.12.2020.
//

#include "Worker.h"
#include "gtest/gtest.h"
#include <string>
#include <queue>
#include <utility>


typedef std::map<std::string, std::string> Context;

struct Request {
    explicit Request(Context context) : context(std::move(context)) {};
    static void call_back(const std::string& string) {
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


TEST(WorkerTests, TimeWork){

    Context context = {{"METHOD", "GET"}};
    Queue queue;

    queue.push(Request(context));
    queue.push(Request(context));
    queue.push(Request(context));
    queue.push(Request(context));
    Worker<Queue, MockHandler>::start_work(queue);
    sleep(3);
    Worker<Queue, MockHandler>::stop_work();
    ASSERT_TRUE(queue.empty());
}
