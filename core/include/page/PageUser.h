//
// Created by sergei on 28.11.2020.
//

#pragma once

#include "PageManager.h"

template<class View>
class PageUser : public PageManager<View> {
public:
    explicit PageUser(const View& view) : PageManager<View>(view) {};
    ~PageUser() override = default;
    PageUser(const PageUser&) = delete;
    PageUser& operator = (PageUser&) = delete;

    string get_main_page() const override;

    string get_room_page(int id) const override;

    string get_favorite_page() const override;

    string get_deadline_page() const override;

    string get_registr_page() const override;

    string get_login_page() const override;

    string get_info_tags(int id_room, std::unique_ptr<std::vector<string>> tags) const override;

    string get_not_found() const override;
};
