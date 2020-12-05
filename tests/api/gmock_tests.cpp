//
// Created by sergei on 29.11.2020.
//

//#include "Worker.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <string>

using ::testing::AtLeast;
using ::testing::SetArgReferee;
using ::testing::DoAll;
using ::testing::Return;

class MockWorker {
public:
    MOCK_METHOD0(start_work, std::string());
};

TEST(TestsIntegrate, MainPage){
//    Queue q;
//    MockWorker work;
//    EXPECT_CALL(work, start_work)
//            .WillOnce(DoAll(Return("str")));
//
//    Worker worker(q);
//    ASSERT_TRUE(worker.start_work() == "str");
}


using ::testing::AtLeast;
using ::testing::SetArgReferee;
using ::testing::DoAll;
using ::testing::Return;


typedef std::map<std::string, std::string> Context;
class MockView {
public:
    MOCK_METHOD(std::string , render, (Context));
};

TEST(PageUserTests, MainPage){
    MockView mv;
    Context context = {{"Page", "main"}};
    EXPECT_CALL(mv, render)
            .WillOnce(DoAll(Return("main")));

    PageUser<MockView> page(mv);
    EXPECT_EQ(page.get_main_page(), "main");
}