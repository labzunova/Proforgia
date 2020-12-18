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

    std::string get_profile_page() override;

    std::string get_room_page(std::string id) override;

    std::string get_favorite_page() override;

    std::string get_deadline_page() override;

    std::string get_signup_page() override;

    std::string get_login_page() override;

    std::string get_info_tags(std::string id_room, std::unique_ptr<std::vector<std::string>> tags) override;

    std::string get_not_found() override;

    std::string get_server_err() override;
};
