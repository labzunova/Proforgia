//
// Created by sergei on 28.11.2020.
//

#pragma once

#include "View.h"
#include <string>
#include <vector>
#include <memory>

using std::string;

template<class View>
class PageManager {
protected:
    explicit PageManager(const View& view) : view_(std::move(view)) {}

private:
    PageManager(const PageManager&) = default;
    PageManager& operator = (PageManager&) = default;

public:
    virtual ~PageManager() = default;

    virtual string get_main_page() const = 0;
    virtual string get_room_page(int id) const = 0;
    virtual string get_favorite_page() const = 0;
    virtual string get_deadline_page() const = 0;
    virtual string get_registr_page() const = 0;
    virtual string get_login_page() const = 0;
    virtual string get_info_tags(int id_room, std::unique_ptr<std::vector<string>> tags) const = 0;
    virtual string get_not_found() const = 0;

protected:
    View view_;
};
