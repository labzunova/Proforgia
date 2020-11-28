//
// Created by sergei on 28.11.2020.
//

#pragma once

#include "external_api/View.h"
#include <string>
#include <vector>

using std::string;

class PageManager {
protected:
    explicit PageManager(const View& view) : view_(view) {}
    ~PageManager() = default;

private:
    PageManager(const PageManager&) = default;
    PageManager& operator = (PageManager&) = default;

public:

    virtual string get_main_page() const = 0;
    virtual string get_room_page(int id) const = 0;
    virtual string get_favorite_page() const = 0;
    virtual string get_deadline_page() const = 0;
    virtual string get_registr_page() const = 0;
    virtual string get_login_page() const = 0;
    virtual string get_info_tags(int id_room, std::vector<string> tags) const = 0;
    virtual string get_not_found() const = 0;

private:
    View view_;
};
