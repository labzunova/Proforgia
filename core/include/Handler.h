//
// Created by sergei on 28.11.2020.
//

#pragma once

#include "PageManager.h"
#include "ActivityManager.h"
#include "View.h"
#include "DBEntities.h"
#include "ErrorCodes.h"

#include <string>
#include <map>
#include <memory>

#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/local_time/local_time.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

using std::string;
using namespace boost::posix_time;

typedef std::map<std::string, std::string> Context;

class Handler {
private:
    enum Status {
        OK,
        Rotten,
        NotFound,
    };

public:
    explicit Handler(Context& context) : context_(context) {};
    ~Handler() = default;
    Handler(const Handler&) = delete;
    Handler& operator=(const Handler&) = delete;

    std::string get_respons();

private:
    void start_session();
    Status check_session(DBSession& session);
    static string redirect(const string& page);
    void set_user_right();

private:
//    const boost::posix_time::ptime now= boost::posix_time::second_clock::local_time();
//    boost::local_time::local_date_time LIVE_TIME =;

    const time_duration LIVE_TIME = hours(100);

    Context context_;

    PageManager* page_manager_;
    ActivityManager* activity_manager_;
};
