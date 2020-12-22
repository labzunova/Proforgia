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

    Status get_signup_page(std::string& body) override;

    Status get_login_page(std::string& body) override;

    Status get_not_found(std::string& body) override;

    Status get_server_err(std::string& body) override;
};
