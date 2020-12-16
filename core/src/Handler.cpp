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


    start_session();

    if(context_.find("path") == context_.end()) {
        return page_manager_->get_not_found();
    }

    if(context_["method"] == "POST") {
        if(context_["path"] == "signup") {
            auto code = activity_manager_->signUp();
            if(code == ActivityManager::CLIENT_ERROR)
                return page_manager_->get_registr_page();

            else if(code == ActivityManager::SERVER_ERROR)
                return page_manager_->get_server_err();

            else {
                // TODO запись сессии
                return redirect("MAIN");
            }
        }
        else if(context_["path"] == "login") {
            auto code = activity_manager_->signIn();
            if(code == ActivityManager::CLIENT_ERROR)
                return page_manager_->get_login_page();

            else if(code == ActivityManager::SERVER_ERROR)
                return page_manager_->get_server_err();

            else {
                // TODO запись сессии
                return redirect("MAIN");
            }
        }
        else if(context_["path"] == "room") {
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
        if(context_["path"] == "profile") {
            ContextMap ctx = {{"code", "200"}};
            set_header_data(ctx);
            string body = page_manager_->get_main_page();
            ctx["content-length"] = body.size();
            ctx["body"] = body;
            return HttpResponse::get_response(ctx);

        } else if(context_["path"] == "login") {
            ContextMap ctx = {{"code", "200"}};
            set_header_data(ctx);
            string body = page_manager_->get_login_page();
            ctx["content-length"] = body.size();
            ctx["body"] = body;
            return HttpResponse::get_response(ctx);

        } else if(context_["path"] == "signup") {
            ContextMap ctx = {{"code", "200"}};
            set_header_data(ctx);
            string body = page_manager_->get_registr_page();
            ctx["content-length"] = body.size();
            ctx["body"] = body;
            return HttpResponse::get_response(ctx);

        } else if(context_["path"] == "roomtag") {
            // TODO запись id комнаты в context_
            auto tags = std::make_unique<std::vector<std::string>>();
            tags->push_back(context_["tag"]);

            ContextMap ctx = {{"code", "200"}};
            set_header_data(ctx);
            string body = page_manager_->get_info_tags(boost::lexical_cast<int>(context_["id_room"]), std::move(tags));
            ctx["content-length"] = body.size();
            ctx["body"] = body;
            return HttpResponse::get_response(ctx);

        }
    }
}

// создаем разные обработики событий взависимости от того
// есть ли сессия
void Handler::start_session() {
    ContextMap ctx; // TODO запись в контекст нужной информации


    /////// тест для бд ///////
//    ErrorCodes er;
//    auto user = DBUser::get(1, er);
//    page_manager_ = std::make_unique<PageCustomer>(user);
//    activity_manager_ = std::make_unique<ActivityCustomer>(ctx, user);
//    return;
    //////////////////////////



    /// временное решение
    set_user_right();

    /// записать user тоже временное решение
    std::shared_ptr<DBUser> user = std::make_shared<DBUser>();
    page_manager_ = std::make_unique<PageCustomer>(user);
    activity_manager_ = std::make_unique<ActivityCustomer>(ctx, std::move(user));

    /// вернуться когда будет готов интерфейс сессии
//    if(context_.find("session") == context_.end()) {
//        set_user_right();
//        return;
//    }

    // DBSession session = DBSession::get(context_["session"]);

//    if (check_session(session) == Handler::OK) {
//        BOOST_LOG_TRIVIAL(debug) << "Start customer session";
//
//        DBUser user = DBUser::get(session.get_user());
//        page_manager_ = std::make_unique<PageCustomer>(user);
//        activity_manager_ = std::make_unique<ActivityCustomer>(ctx, std::move(user));
//    } else {
//        set_user_right();
//    }
}


/// вернуться сюда, когда ваня доделает интерфейс сессии
// проверяем пришедшую сессию, не протухла ли
Handler::Status Handler::check_session(DBSession& session) {

    return OK;  /// временное решение

    // date start_time = session.date_of_creation;
//    ptime today = second_clock::local_time(); // TODO подумать над временем часового пояса
//    if(today > ptime(start_time, LIVE_TIME))
//         // TODO удаление ссесии
//        return Rotten;
//    else
//        return OK;
}

string Handler::redirect(const string& page) {
    ContextMap ctx = {{"code",     "302"},
                      {"location", page}}; // TODO заполнение контекста
    return HttpResponse::get_response(ctx);
}

void Handler::set_user_right() {
    BOOST_LOG_TRIVIAL(debug) << "Start user session";
    page_manager_ = std::make_unique<PageUser>();
    ContextMap ctx = {};  // TODO подумать что нужно передать в этот контекст
    activity_manager_ = std::make_unique<ActivityUser>(ctx);
}

void Handler::set_header_data(ContextMap& context) {
    context["date"] = to_simple_string(second_clock::local_time());
    context["server"] = "OurBestServer 0.1";
}


