//
// Created by sergei on 28.11.2020.
//

#pragma once

#include "PageManager.h"
#include "ActivityManager.h"
#include "DBEntities.h"
#include "ErrorCodes.h"

#include <string>
#include <map>
#include <memory>

#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/local_time/local_time.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"


typedef std::map<std::string, std::string> ContextMap;

class Handler {
private:
    enum Status {
        OK,
        Rotten,
        NotFound,
    };

public:
    explicit Handler(ContextMap& context) : context_(context) {};
    ~Handler() = default;
    Handler(const Handler&) = delete;
    Handler& operator=(const Handler&) = delete;

    std::string get_response();

private:
    void start_session();
    Status check_session(DBSession& session);
    string redirect(const string& page);
    void set_user_right();
    void set_customer_right(std::shared_ptr<DBUser>& user);
    void set_header_data(ContextMap& context);

private:
    const time_duration LIVE_TIME = hours(100);

    ContextMap context_;

    std::unique_ptr<PageManager> page_manager_;
    std::unique_ptr<ActivityManager> activity_manager_;
};
