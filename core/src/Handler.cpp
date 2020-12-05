//
// Created by sergei on 28.11.2020.
//

#include "Handler.h"
#include "PageUser.h"
#include "PageCustomer.h"
#include "ActivityUser.h"
#include "ActivityCustomer.h"
#include "entities.h"
#include <boost/lexical_cast.hpp>

using namespace boost::gregorian;

std::string Handler::get_response() {
    start_session();

    if(context_.find("action") == context_.end()) {
        return page_manager_->get_not_found();
    }

    if(context_["method"] == "POST") {
        if(context_["action"] == "")

    } else {
        if(context_["action"] == "MAIN") {
            return page_manager_->get_main_page();

        } else if(context_["action"] == "LOGIN") {
            return page_manager_->get_login_page();

        } else if(context_["action"] == "SIGNUP") {
            return page_manager_->get_registr_page();

        } else if(context_["action"] == "FILES_BY_TAG") {
            // TODO запись id комнаты в context_
            auto tags = std::make_unique<std::vector<std::string>>();
            tags->push_back(context_["tag"]);
            return page_manager_->get_info_tags(boost::lexical_cast<int>(context_["id_room"]), std::move(tags));

        }
    }
}

void Handler::start_session() {
    View view; // TODO получаем другим способом(синголтоном)
    Context ctx; // TODO запись в контекст нужной информации

    if (check_session() == Handler::OK) {
        DBUser user = DBUser::get(DBSession::get("session").get_user());
        page_manager_ = std::make_shared<PageCustomer<View, DBUser>>(view, user);
        activity_manager_ = std::make_shared<ActivityCustomer<DBUser>>(ctx, user);
    } else {
        page_manager_ = std::make_shared<PageUser<View>>(view);
        activity_manager_ = std::make_shared<ActivityUser<DBUser, DBSession>>(DBSession::get("session"))
    }
}

Handler::Status Handler::check_session() {
    if(context_.find("session") == context_.end()) {
        return NotFound;
    }

    date today = day_clock::local_day();
    days days_live = today - DBSession::get(context_["session"]).date_of_creation;
    if(days_live > LIVE_TIME)
        return Rotten;
    else
        return OK;
}

std::string Handler::redirect() {
    return std::__cxx11::string();
}
