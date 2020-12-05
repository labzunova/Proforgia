//
// Created by sergei on 02.12.2020.
//

#include "PageUser.h"
#include "gtest/gtest.h"
#include <string>


class TestView {
public:
    std::string render(Context context) {
        std::string response;

        response = "page: " + context["page"] +
                "user_name: " + context["user_name"] +
                "room_name: " + context["room_name"];

        return response;
    }
};

class RoomTest {
private:
    explicit RoomTest(int id) { room_name = room_name + std::to_string(id); }

public:
    std::string room_name = "Room Test";

    static RoomTest get(int id) {
        return RoomTest(id);
    }
};

class UserTest {
private:
    explicit UserTest(int id) { user_name = user_name + std::to_string(id); }

public:
    std::string user_name = "User Test";

    static UserTest get(int id) {
        return UserTest(id);
    }
};


TEST(PageUserTests, MainPage){
    TestView view;
    PageUser<TestView> page(view);
    std::string response = "page: MAIN";
    EXPECT_EQ(response, page.get_main_page());
}
