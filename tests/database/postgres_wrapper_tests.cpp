#include "gtest/gtest.h"
#include <iostream>
#include "../../database/include/Utils/DBEntities.h"

TEST(QueryDataTests, TestQuery){
    ErrorCodes error;

    auto room = DBRoom::get(2, error);
    auto room_posts = room->get_posts(error);
    if (room_posts) {
        for (int i = 0; i < room_posts->size(); i++) {
            room_posts.value()[i].print();
            std::cout << std::endl;
        }
    } else assert(false);
    EXPECT_EQ(room_posts.value()[room_posts->size()-1].get_id(), 3);
}
