//
// Created by sergei on 28.11.2020.
//

#pragma once

#include "PageManager.h"
#include "DBEntities.h"
#include "ErrorCodes.h"


#include <map>
#include <string>

class PageCustomer : public PageManager {
public:
    explicit PageCustomer(std::shared_ptr<DBUser>& user);
    ~PageCustomer() override = default;
    PageCustomer(const PageCustomer&) = delete;
    PageCustomer& operator = (PageCustomer&) = delete;

    std::string get_profile_page() override;

    std::string get_room_page(std::string id) override;

    std::string get_favorite_page() override;

    std::string get_deadline_page() override;

    std::string get_signup_page() override;

    std::string get_login_page() override;

    std::string get_info_tags(std::string id_room, std::unique_ptr<std::vector<std::string>> tags) override;

    std::string get_not_found() override;

    std::string get_server_err() override;

private:
    void write_user(Context::User &user);
    void write_room(Context::Room &room, const std::shared_ptr<DBRoom> &db_room);
    void write_info_tag(Context& ctx, const DBRoom& room, std::string tag);

    static void set_tags(std::vector<DBTag>& input, std::vector<Context::Tag>& output);
    static void set_posts(std::vector<DBPost>& input, std::vector<Context::Post>& output);

private:
    std::shared_ptr<DBUser> user_;
};
