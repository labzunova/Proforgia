//
// Created by sergei on 28.11.2020.
//

#include "HttpResponse.h"
#include "Handler.h"
#include "PageUser.h"
#include "PageCustomer.h"
#include "ActivityUser.h"
#include "ActivityCustomer.h"
#include <boost/lexical_cast.hpp>
#include <boost/log/trivial.hpp>

using namespace boost::gregorian;

std::string Handler::get_response() {
    start_session();

    /////// для теста шаблонизатора ///////
//    Context ctx = {{"code", "200"}};
//    std::string body = page_manager_->get_login_page();
//    ctx["body"] = body;
//    ctx["date"] = to_iso_string(second_clock::local_time());
//    ctx["server"] = "SERVER";
//    ctx["content-length"] = body.size();
//    return HttpResponse::get_response(ctx);
    /////////////////////////



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

// создаем разные обработики событий взависимости от того
// есть ли сессия
void Handler::start_session() {
    Context ctx; // TODO запись в контекст нужной информации


    /////// тест для бд ///////
//    ErrorCodes er;
//    DBUser user = DBUser::get(1, er);
//    page_manager_ = std::make_unique<PageCustomer>(user);
//    activity_manager_ = std::make_unique<ActivityCustomer>(ctx, std::move(user));
    //////////////////////////


    if(context_.find("session") == context_.end()) {
        set_user_right();
        return;
    }

    DBSession session = DBSession::get(context_["session"]);

    if (check_session(session) == Handler::OK) {
        BOOST_LOG_TRIVIAL(debug) << "Start user session";

        DBUser user = DBUser::get(session.get_user());
        page_manager_ = std::make_unique<PageCustomer>(user);
        activity_manager_ = std::make_unique<ActivityCustomer>(ctx, std::move(user));
    } else {
        set_user_right();
    }
}


// проверяем пришедшую сессию, не протухла ли
Handler::Status Handler::check_session(DBSession& session) {

    date start_time = session.date_of_creation;
    ptime today = second_clock::local_time(); // TODO подумать над временем часового пояса
    if(today > ptime(start_time, LIVE_TIME))
         // TODO удаление ссесии
        return Rotten;
    else
        return OK;
}

string Handler::redirect(const string& page) {
    Context ctx = {{"code", "302"},
                    {"location", page}}; // TODO заполнение контекста
    return HttpResponse::get_response(ctx);
}

void Handler::set_user_right() {
    BOOST_LOG_TRIVIAL(debug) << "Start customer session";
    page_manager_ = std::make_unique<PageUser>();
    activity_manager_ = std::make_unique<ActivityUser>(DBSession::get("session"));
}
