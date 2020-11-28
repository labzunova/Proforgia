//
// Created by sergei on 28.11.2020.
//

#pragma once

#include "PageManager.h"
#include "ActivityManager.h"

#include <string>
#include <map>
#include <memory>

typedef std::map<std::string, std::string> Context;

class Handler {
private:
    enum Status {
        OK,
        Rotten,
    };

public:
    explicit Handler(Context& context) : context_(context) {};
    ~Handler() = default;
    Handler(const Handler&) = delete;
    Handler& operator=(const Handler&) = delete;

    std::string start_process();

private:
    void start_session();
    Status check_session();

private:
    Context context_;

    std::unique_ptr<PageManager> page_manager_;
    std::unique_ptr<ActivityManager> activity_manager_;
};
