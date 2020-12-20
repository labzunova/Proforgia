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
public:
    enum Status {
        OK,
        SERVER_ERROR,
        CLIENT_ERROR_RIGHT,
        CLIENT_ERROR_VALID,
    };

protected:
    explicit PageManager() = default;

private:
    PageManager(const PageManager&) = delete;
    PageManager& operator = (PageManager&) = delete;

public:
    virtual ~PageManager() = default;

    virtual Status get_profile_page(std::string& body);
    virtual Status get_room_page(std::string& body, std::string id_room);
    virtual Status get_add_content_page(std::string& body, std::string id_room);
    virtual Status get_favorite_page(std::string& body);
    virtual Status get_deadline_page(std::string& body);
    virtual Status get_signup_page(std::string& body);
    virtual Status get_login_page(std::string& body);
    virtual Status get_info_tags(std::string& body, std::string id_room, std::unique_ptr<std::vector<std::string>> tags);
    virtual Status get_not_found(std::string& body);
    virtual Status get_server_err(std::string& body);
};
