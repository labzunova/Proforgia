//
// Created by sergei on 28.11.2020.
//

#include "PageCustomer.h"

#include <utility>

string PageCustomer::get_main_page() const {
    return std::__cxx11::string();
}

string PageCustomer::get_room_page(int id) const {
    return std::__cxx11::string();
}

string PageCustomer::get_favorite_page() const {
    return std::__cxx11::string();
}

string PageCustomer::get_deadline_page() const {
    return std::__cxx11::string();
}

string PageCustomer::get_registr_page() const {
    return std::__cxx11::string();
}

string PageCustomer::get_login_page() const {
    return std::__cxx11::string();
}

string PageCustomer::get_info_tags(int id_room, std::vector<string> tags) const {
    return std::__cxx11::string();
}

string PageCustomer::get_not_found() const {
    return std::__cxx11::string();
}

PageCustomer::PageCustomer(const View &view, const User& user)
        : PageManager(view)
        , user_(user) {}

void PageCustomer::write_user(std::map<string, string> &ctx) {

}

void PageCustomer::write_room(std::map<string, string> &ctx, const Room &room) {

}

void PageCustomer::write_info_tag(std::map<string, string> &ctx, const Room &room, string tag) {

}
