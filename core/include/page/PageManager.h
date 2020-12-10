//
// Created by sergei on 28.11.2020.
//

#pragma once

//#include "TemplateWrapper.h"
#include <string>
#include <vector>
#include <memory>

using std::string;

class PageManager {
protected:
    explicit PageManager() {
        // TODO из синголтона достаем view
    }

private:
    PageManager(const PageManager&) = default;
    PageManager& operator = (PageManager&) = default;

public:
    virtual ~PageManager() = default;

    virtual string get_main_page() = 0;
    virtual string get_room_page(string id) = 0;
    virtual string get_favorite_page() = 0;
    virtual string get_deadline_page() = 0;
    virtual string get_registr_page() = 0;
    virtual string get_login_page() = 0;
    virtual string get_info_tags(int id_room, std::unique_ptr<std::vector<string>> tags) = 0;
    virtual string get_not_found() = 0;
    virtual string get_server_err() = 0;

protected:
//    TemplateWrapper view_;
};
