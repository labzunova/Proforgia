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

    Status get_profile_page(std::string& body) override;

    Status get_room_page(std::string& body, std::string id) override;

    Status get_favorite_page(std::string& body) override;

    Status get_deadline_page(std::string& body) override;

    Status get_signup_page(std::string& body) override;

    Status get_login_page(std::string& body) override;

    Status get_info_tags(std::string& body, std::string id_room, std::unique_ptr<std::vector<std::string>> tags) override;

    Status get_not_found(std::string& body) override;

    Status get_server_err(std::string& body) override;

private:
    void write_user(Context::User &user);
    void write_room(Context::Room &room, const std::shared_ptr<DBRoom> &db_room);
    void write_info_tag(Context& ctx, const DBRoom& room, std::string tag);

    static void set_tags(std::vector<DBTag>& input, std::vector<Context::Tag>& output);
    static void set_posts(std::vector<DBPost>& input, std::vector<Context::Post>& output);

private:
    std::shared_ptr<DBUser> user_;
};
