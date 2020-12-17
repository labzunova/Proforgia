//
// Created by sergei on 28.11.2020.
//

#pragma once

#include "PageManager.h"

class PageUser : public PageManager {
public:
    explicit PageUser() = default;;
    ~PageUser() override = default;
    PageUser(const PageUser&) = delete;
    PageUser& operator = (PageUser&) = delete;

    string get_profile_page() override;

    string get_room_page(string id) override;

    string get_favorite_page() override;

    string get_deadline_page() override;

    string get_signup_page() override;

    string get_login_page() override;

    string get_info_tags(string id_room, std::unique_ptr<std::vector<string>> tags) override;

    string get_not_found() override;

    string get_server_err() override;
};
