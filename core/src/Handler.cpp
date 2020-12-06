//
// Created by sergei on 28.11.2020.
//

#include "HttpResponse.h"
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
        if(context_["action"] == "signup") {
            auto code = activity_manager_->signUp();
            if(code == ActivityManager::CLIENT_ERROR)
                return page_manager_->get_registr_page();

            else if(code == ActivityManager::SERVER_ERROR)
                return page_manager_->get_server_err();

            else
                return redirect("MAIN");
        }
        else if(context_["action"] == "login") {
            auto code = activity_manager_->signIn();
            if(code == ActivityManager::CLIENT_ERROR)
                return page_manager_->get_login_page();

            else if(code == ActivityManager::SERVER_ERROR)
                return page_manager_->get_server_err();

            else
                return redirect("MAIN");
        }
        else if(context_["action"] == "add_file") {
            auto code = activity_manager_->add_content();
            if(code == ActivityManager::CLIENT_ERROR)
                return page_manager_->get_room_page(context_["id_room"]);

            else if(code == ActivityManager::SERVER_ERROR)
                return page_manager_->get_server_err();

            else
                return redirect("ROOM/" + context_["id_room"]); // TODO не понятно в каком формате отдавать ссылку
        }

    }
    else {
        if(context_["action"] == "MAIN") {
            Context ctx = {{"code", "200"}}; // TODO заполнение контекста
            ctx["body"] = page_manager_->get_main_page();
            return HttpResponse::get_response(ctx);

        } else if(context_["action"] == "LOGIN") {
            Context ctx = {{"code", "200"}}; // TODO заполнение контекста
            ctx["body"] = page_manager_->get_login_page();
            return HttpResponse::get_response(ctx);

        } else if(context_["action"] == "SIGNUP") {
            Context ctx = {{"code", "200"}}; // TODO заполнение контекста
            ctx["body"] = page_manager_->get_registr_page();
            return HttpResponse::get_response(ctx);

        } else if(context_["action"] == "FILES_BY_TAG") {
            // TODO запись id комнаты в context_
            auto tags = std::make_unique<std::vector<std::string>>();
            tags->push_back(context_["tag"]);

            Context ctx = {{"code", "200"}}; // TODO заполнение контекста
            ctx["body"] = page_manager_->get_info_tags(boost::lexical_cast<int>(context_["id_room"]), std::move(tags));
            return HttpResponse::get_response(ctx);

        }
    }
}

void Handler::start_session() {
    View view; // TODO получаем другим способом(синголтоном)
    Context ctx; // TODO запись в контекст нужной информации

    if (check_session() == Handler::OK) {
        DBUser user = DBUser::get(DBSession::get("session").get_user());
        page_manager_ = std::make_shared<PageCustomer<View, DBUser, DBSession>>(view, user);
        activity_manager_ = std::make_shared<ActivityCustomer<DBUser, DBRoom, DBSession>>(ctx, user);
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

string Handler::redirect(const string& page) {
    Context ctx = {{"code", "302"},
                    {"location", page}}; // TODO заполнение контекста
    return HttpResponse::get_response(ctx);
}
