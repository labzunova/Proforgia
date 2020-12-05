//
// Created by sergei on 28.11.2020.
//

#pragma once

#include "PageManager.h"

#include <map>
#include <string>

using std::string;

template<class View, class User, class Room>
class PageCustomer : public PageManager<View> {
public:
    PageCustomer(const View& view, const User& user);
    ~PageCustomer() override = default;
    PageCustomer(const PageCustomer&) = delete;
    PageCustomer& operator = (PageCustomer&) = delete;

    string get_main_page() const override;

    string get_room_page(int id) const override;

    string get_favorite_page() const override;

    string get_deadline_page() const override;

    string get_registr_page() const override;

    string get_login_page() const override;

    string get_info_tags(int id_room, std::unique_ptr<std::vector<string>> tags) const override;

    string get_not_found() const override;

private:
    void write_user(std::map<string, string>& ctx);
    void write_room(std::map<string, string>& ctx, const Room& room);
    void write_info_tag(std::map<string, string>& ctx, const Room& room, string tag);

private:
    User user_;
};
