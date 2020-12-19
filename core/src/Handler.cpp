//
// Created by sergei on 28.11.2020.
//

#include "HttpResponse.h"
#include "Handler.h"
#include "PageUser.h"
#include "PageCustomer.h"
#include "ActivityUser.h"
#include "ActivityCustomer.h"
#include <boost/log/trivial.hpp>

using namespace boost::gregorian;

std::string Handler::get_response() {

    /////// для теста шаблонизатора ///////
//    page_manager_ = std::make_unique<PageUser>();
//    ContextMap ctx = {{"code", "200"}};
//    std::string body = page_manager_->get_login_page();
//    ctx["body"] = body;
//    ctx["date"] = to_iso_string(second_clock::local_time());
//    ctx["server"] = "SERVER";
//    ctx["content-length"] = body.size();
//    return HttpResponse::get_response(ctx);
    /////////////////////////

    BOOST_LOG_TRIVIAL(debug) << "Session Length: " + std::to_string(context_["session"].size());

    start_session();

//    if(context_.find("path") == context_.end()) {
//        return page_manager_->get_not_found();
//    }


    string body;
    ContextMap context_response = {{"Code", "200 OK"}};

    if(context_["method"] == "POST") {
        if(context_["path"] == "signup") {
            string session;
            auto code = activity_manager_->signUp(session);
            if(code == ActivityManager::CLIENT_ERROR)
                body = page_manager_->get_signup_page();

            else if(code == ActivityManager::SERVER_ERROR)
                body = page_manager_->get_server_err(); //// лучше редиректом

            else {
                context_["new_session"] = session;
                return redirect("/profile");
            }
        }
        else if(context_["path"] == "login") {
            string session;
            auto code = activity_manager_->login(session);
            if(code == ActivityManager::CLIENT_ERROR)
                body = page_manager_->get_login_page();

            else if(code == ActivityManager::SERVER_ERROR)
                body = page_manager_->get_server_err();

            else {
                context_["new_session"] = session;
                return redirect("/profile");
            }
        }
        else if(context_["path"] == "create") {
            auto code = activity_manager_->create_room();
            if(code == ActivityManager::CLIENT_ERROR)
                body = page_manager_->get_profile_page();

            else if(code == ActivityManager::SERVER_ERROR)
                body = page_manager_->get_server_err();

            else {
                return redirect("/profile");
            }
        }
        else if(context_["path"] == "join") {
            auto code = activity_manager_->add_room();
            if(code == ActivityManager::CLIENT_ERROR)
                body = page_manager_->get_profile_page();

            else if(code == ActivityManager::SERVER_ERROR)
                body = page_manager_->get_server_err();

            else {
                return redirect("/profile");
            }
        }
        else if(context_["path"] == "room") {
            auto code = activity_manager_->add_content();
            if(code == ActivityManager::CLIENT_ERROR)
                return page_manager_->get_room_page(context_["id_room"]);

            else if(code == ActivityManager::SERVER_ERROR)
                return page_manager_->get_server_err();

            else
                return redirect("/room/" + context_["id_room"]);
        }

    }
    else {
        if(context_["path"] == "profile") {
            body = page_manager_->get_profile_page();

        } else if(context_["path"] == "login") {
            body = page_manager_->get_login_page();

        } else if(context_["path"] == "signup") {
            body = page_manager_->get_signup_page();

        } else if(context_["path"] == "room") {
            body = page_manager_->get_room_page(context_["room"]);

            if (body.empty())
                return redirect("/profile");

        } else if(context_["path"] == "roomtag") {
            // TODO запись id комнаты в context_
            auto tags = std::make_unique<std::vector<std::string>>();
            tags->push_back(context_["tag"]);

            // boost::lexical_cast<int>(context_["id_room"])
            body = page_manager_->get_info_tags(context_["roomID"], std::move(tags));
        } else {
            body = page_manager_->get_not_found();
            context_response["Code"] =  "404 Not Found";

        }
    }

    set_header_data(context_response);
    context_response["Content-Length"] = std::to_string(body.size());
    context_response["Body"] = body;
    return HttpResponse::get_response(context_response);
}

// создаем разные обработики событий взависимости от того
// есть ли сессия
void Handler::start_session() {


    /////// тест для бд ///////
//    ErrorCodes er;
//    auto user = DBUser::get(1, er);
//    page_manager_ = std::make_unique<PageCustomer>(user);
//    activity_manager_ = std::make_unique<ActivityCustomer>(ctx, user);
//    return;
    //////////////////////////



    /// временное решение
//    set_user_right();

    /// записать user тоже временное решение
//    std::shared_ptr<DBUser> user = std::make_shared<DBUser>();
//    page_manager_ = std::make_unique<PageCustomer>(user);
//    activity_manager_ = std::make_unique<ActivityCustomer>(ctx, std::move(user));

    /// вернуться когда будет готов интерфейс сессии
    if(context_.find("session") == context_.end() || context_["session"].empty()) {
        set_user_right();
        return;
    }

    ErrorCodes er;
    auto session = DBSession::get(context_["session"], er);

    if (!session) {
        set_user_right();
        return;
    }

    if (check_session(session) == Handler::OK) {
        std::shared_ptr<DBUser> user = session->get_user(er);
        set_customer_right(user);
    } else {
        set_user_right();
    }
}


// проверяем пришедшую сессию, не протухла ли
Handler::Status Handler::check_session(std::shared_ptr<DBSession>& session) {

    auto start_time = session->getCreationDate();
    // TODO поставить правильное время
    string posix_tz_def("PST-5PDT01:00:00,M4.1.0/02:00:00,M10.1.0/02:00:00");
    local_date_time today(second_clock::local_time(),
                                time_zone_ptr(new posix_time_zone(posix_tz_def)));
    if(today > start_time + LIVE_TIME)
         // TODO удаление ссесии
        return Rotten;
    else
        return OK;
}

string Handler::redirect(const string& page) {
    BOOST_LOG_TRIVIAL(info) << "redirect";

    ContextMap ctx = {{"Code",     "302 Found"},
                      {"Location", page}};

    set_header_data(ctx);
    return HttpResponse::get_response(ctx);
}

void Handler::set_user_right() {
    BOOST_LOG_TRIVIAL(info) << "Start user session";
    page_manager_ = std::make_unique<PageUser>();
    ContextMap ctx = context_;  // TODO подумать что нужно передать в этот контекст
    activity_manager_ = std::make_unique<ActivityUser>(context_);
}

void Handler::set_customer_right(std::shared_ptr<DBUser>& user) {
    BOOST_LOG_TRIVIAL(info) << "Start customer session";

    ContextMap ctx = context_; // TODO заполнить контекст
    page_manager_ = std::make_unique<PageCustomer>(user);
    activity_manager_ = std::make_unique<ActivityCustomer>(ctx, std::move(user));
}

void Handler::set_header_data(ContextMap& context) {
    context["Date"] = to_simple_string(second_clock::local_time());
    context["Server"] = "OurBestServer 0.1";
    context["Content-Type"] = "text/html; charset=utf-8";
    if(context_.find("new_session") != context_.end()) {
        auto time = second_clock::local_time() + LIVE_TIME;
        context["Set-Cookie"] = "session=" + context_["new_session"] + "; "
                + "expires=Thu," + to_simple_string(time) + "; "
                + "HttpOnly; "
                + "Max - Age = " + std::to_string(LIVE_TIME.total_seconds()) + "; "
                + "Path =/; ";
    }
}


