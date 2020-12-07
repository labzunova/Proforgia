//
// Created by sergei on 02.12.2020.
//

#include "page/PageUser.cpp"
#include "gtest/gtest.h"
#include <string>


class TestView {
public:
    std::string render(Context& context) {
        std::string response;

        response = "page: " + context["page"] + "\n";
        if(context.find("user_name") != context.end())
            response += "user_name: " + context["user_name"] + "\n";
        if(context.find("room_name") != context.end())
            response += "room_name: " + context["room_name"] + "\n";

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
    std::string response = "page: MAIN\n";
    EXPECT_EQ(response, page.get_main_page());
    EXPECT_EQ(response, page.get_room_page("5"));
    EXPECT_EQ(response, page.get_deadline_page());
    EXPECT_EQ(response, page.get_favorite_page());
    EXPECT_EQ(response, page.get_info_tags(5, nullptr));
}
