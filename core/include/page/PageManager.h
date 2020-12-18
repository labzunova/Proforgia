//
// Created by sergei on 28.11.2020.
//

#pragma once


#include "TemplateWrapper.h"
#include "Context.h"
#include <string>
#include <vector>
#include <memory>
#include <map>

class PageManager {
protected:
    explicit PageManager() = default;

private:
    PageManager(const PageManager&) = delete;
    PageManager& operator = (PageManager&) = delete;

public:
    virtual ~PageManager() = default;

    virtual std::string get_profile_page() = 0;
    virtual std::string get_room_page(std::string id_room) = 0;
    virtual std::string get_favorite_page() = 0;
    virtual std::string get_deadline_page() = 0;
    virtual std::string get_signup_page() = 0;
    virtual std::string get_login_page() = 0;
    virtual std::string get_info_tags(std::string id_room, std::unique_ptr<std::vector<std::string>> tags) = 0;
    virtual std::string get_not_found() = 0;
    virtual std::string get_server_err() = 0;
};
