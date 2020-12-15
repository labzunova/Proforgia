//
// Created by sergei on 28.11.2020.
//

#pragma once

#include "PageManager.h"
#include "DBEntities.h"
#include "ErrorCodes.h"


#include <map>
#include <string>

using std::string;

class PageCustomer : public PageManager {
public:
    explicit PageCustomer(std::shared_ptr<DBUser>& user);
    ~PageCustomer() override = default;
    PageCustomer(const PageCustomer&) = delete;
    PageCustomer& operator = (PageCustomer&) = delete;

    string get_main_page() override;

    string get_room_page(string id) override;

    string get_favorite_page() override;

    string get_deadline_page() override;

    string get_registr_page() override;

    string get_login_page() override;

    string get_info_tags(int id_room, std::unique_ptr<std::vector<string>> tags) override;

    string get_not_found() override;

    string get_server_err() override;

private:
    void write_user(std::map<string, string>& ctx);
    void write_room(std::map<string, string>& ctx, const DBRoom& room);
    void write_info_tag(std::map<string, string>& ctx, const DBRoom& room, string tag);

private:
    std::shared_ptr<DBUser> user_;
};
