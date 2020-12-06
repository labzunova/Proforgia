//
// Created by sergei on 28.11.2020.
//

#pragma once

#include "PageManager.h"
#include "ActivityManager.h"
#include "View.h"

#include <string>
#include <map>
#include <memory>

#include "boost/date_time/gregorian/gregorian.hpp"

using std::string;

typedef std::map<std::string, std::string> Context;

class Handler {
private:
    enum Status {
        OK,
        Rotten,
        NotFound,
    };

public:
    explicit Handler(Context& context) : context_(context) {LIVE_TIME(10);};
    ~Handler() = default;
    Handler(const Handler&) = delete;
    Handler& operator=(const Handler&) = delete;

    std::string get_response();

private:
    void start_session();
    Status check_session();
    static string redirect(const string& page);

private:
    boost::gregorian::days LIVE_TIME;

    Context context_;

    std::shared_ptr<PageManager<View>> page_manager_;
    std::shared_ptr<ActivityManager> activity_manager_;
};
