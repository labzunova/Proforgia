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
                page_manager_->get_signup_page(body);

            else if(code == ActivityManager::SERVER_ERROR)
                page_manager_->get_server_err(body); //// лучше редиректом

            else {
                context_["new_session"] = session;
                return redirect("/profile");
            }
        }
        else if(context_["path"] == "login") {
            string session;
            auto code = activity_manager_->login(session);
            if(code == ActivityManager::CLIENT_ERROR)
                page_manager_->get_login_page(body);

            else if(code == ActivityManager::SERVER_ERROR)
                page_manager_->get_server_err(body);

            else {
                context_["new_session"] = session;
                return redirect("/profile");
            }
        }
        else if(context_["path"] == "create") {
            auto code = activity_manager_->create_room();
            if(code == ActivityManager::CLIENT_ERROR)
                page_manager_->get_profile_page(body);

            else if(code == ActivityManager::SERVER_ERROR)
                page_manager_->get_server_err(body);

            else {
                return redirect("/profile");
            }
        }
        else if(context_["path"] == "join") {
            auto code = activity_manager_->add_room();
            if(code == ActivityManager::CLIENT_ERROR)
                page_manager_->get_profile_page(body);

            else if(code == ActivityManager::SERVER_ERROR)
                page_manager_->get_server_err(body);

            else {
                return redirect("/profile");
            }
        }
//        else if(context_["path"] == "room") {
//            auto code = activity_manager_->add_content();
//            if(code == ActivityManager::CLIENT_ERROR)
//                page_manager_->get_room_page(body, context_["id_room"]);
//
//            else if(code == ActivityManager::SERVER_ERROR)
//                page_manager_->get_server_err(body);
//
//            else
//                return redirect("/room/" + context_["id_room"]);
//        }
        else if(context_["path"] == "add") {
            auto code = activity_manager_->add_content();
            if(code == ActivityManager::CLIENT_ERROR)
                page_manager_->get_add_content_page(body, context_["room"], context_["postID"]);

            else if(code == ActivityManager::SERVER_ERROR)
                page_manager_->get_server_err(body);

            else {
                context_["new_postID"] = "";
                return redirect("/room/" + context_["room"]);
            }
        }

    }
    else {
        if (context_["path"].empty())
            return redirect("/profile");

        else if(context_["path"] == "profile") {
            auto status = page_manager_->get_profile_page(body);
            if (status == PageManager::CLIENT_ERROR_RIGHT)
                return redirect("/login");
            else if (status == PageManager::SERVER_ERROR)
                page_manager_->get_server_err(body);

        } else if(context_["path"] == "login") {
            auto status = page_manager_->get_login_page(body);
            if (status == PageManager::CLIENT_ERROR_RIGHT)
                return redirect("/profile");
            else if (status == PageManager::SERVER_ERROR)
                page_manager_->get_server_err(body);

        } else if(context_["path"] == "signup") {
            auto status = page_manager_->get_signup_page(body);
            if (status == PageManager::CLIENT_ERROR_RIGHT)
                return redirect("/profile");
            else if (status == PageManager::SERVER_ERROR)
                page_manager_->get_server_err(body);

        } else if(context_["path"] == "room") {
            auto status = page_manager_->get_room_page(body, context_["room"]);

            if (status == PageManager::CLIENT_ERROR_RIGHT)
                return redirect("/login");
            else if (status == PageManager::SERVER_ERROR)
                page_manager_->get_server_err(body);
            else if (status == PageManager::CLIENT_ERROR_VALID)
                return redirect("/profile");

        } else if(context_["path"] == "roomtag") {
            auto tags = std::make_unique<std::vector<std::string>>();
            tags->push_back(context_["tag"]);

            // boost::lexical_cast<int>(context_["id_room"])
            auto status = page_manager_->get_info_tags(body, context_["room"], std::move(tags));

            if (status == PageManager::CLIENT_ERROR_RIGHT)
                return redirect("/login");
            else if (status == PageManager::SERVER_ERROR)
                page_manager_->get_server_err(body);
            else if (status == PageManager::CLIENT_ERROR_VALID)
                return redirect("/profile");

        } else if (context_["path"] == "logout") { // выход аккаунта
            activity_manager_->exit();

            context_["new_session"] = "";
            return redirect("/login");

        } else if (context_["path"] == "exit") { // выход из комнаты
            activity_manager_->exit_room();

            return redirect("/profile");

        } else if (context_["path"] == "add") {
            auto status = page_manager_->get_add_content_page(body, context_["room"], context_["postID"]);

            context_["new_postID"] = context_["postID"];

            if (status == PageManager::CLIENT_ERROR_RIGHT)
                return redirect("/login");
            else if (status == PageManager::SERVER_ERROR)
                page_manager_->get_server_err(body);
            else if (status == PageManager::CLIENT_ERROR_VALID)
                return redirect("/room/" + context_["roomID"]);

        } else {
            auto status = page_manager_->get_not_found(body);
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
    if(today > start_time + LIVE_TIME) {
        ErrorCodes er;
        DBSession::remove(session->get_id(), er);
        return Rotten;
    }
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
    if(context_.find("new_postID") != context_.end()) {
        auto time = second_clock::local_time() + LIVE_TIME;
        context["Set-Cookie"] = "postID=" + context_["new_postID"] + "; "
                                + "expires=Thu," + to_simple_string(time) + "; "
                                + "HttpOnly; "
                                + "Max - Age = " + std::to_string(LIVE_TIME.total_seconds()) + "; "
                                + "Path =/; ";
    }
}


