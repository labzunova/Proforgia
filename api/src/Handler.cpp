//
// Created by sergei on 28.11.2020.
//

#include "Handler.h"
#include "PageUser.h"
#include "PageCustomer.h"
#include "ActivityUser.h"
#include "ActivityCustomer.h"

std::string Handler::start_process() {
    start_session();

    // TODO определяем запросы и вызываем нужные методы page_manager_ и activity_manager_
}

void Handler::start_session() {
    View view;
    Context ctx;
    if (check_session() == Handler::OK) {
        User user;
        page_manager_ = std::make_unique<PageCustomer>(view, user);
        activity_manager_ = std::make_unique<ActivityCustomer>(ctx, user);
    } else {
        page_manager_ = std::make_unique<PageUser>(view);
        activity_manager_ = std::make_unique<ActivityUser>(ctx);
    }
}

Handler::Status Handler::check_session() {
    // TODO проверка, не протухла ли ссесия
    return OK;
}
