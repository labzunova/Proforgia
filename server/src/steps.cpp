#include "steps.h"
#include "GeneratorKey.h"
#include "DataProcessing.h"

void Step::SetNext(Step* step) {
    next_ = step;
}

Step::Status Step::Next(ContextStr& context) {
    if (next_ != nullptr)
        return next_->Run(context);
    else
        return Status::OK;
}

Step::Status Hash::Run(ContextStr& context) {
    GeneratorKey::GetInstance().HashPassword(context.get("password"));

    return Next(context);
}

Step::Status GenSession::Run(ContextStr& context) {
    std::string session = GeneratorKey::GetInstance().GetSession();
    if (session.empty())
        return Status::SYS_FAILED;

    context.put("session", session);
    return Next(context);
}

Step::Status RoomPrep::Run(ContextStr& context) {
    std::string key = GeneratorKey::GetInstance().GetKey();
    context.put("room_id", key);
    // TODO добавление комнаты в пользовтеля на уровне контекста

    return Next(context);
}

/// создание выходных данных
Step::Status CreateView::Run(ContextStr& context) {
    auto present = new Context<>::InterfacePresent();
    context.GenerationView(present);

    return Next(context);
}

Step::Status SortPopularData::Run(ContextStr& context) {
    DataProcessing::Data data;
    // TODO из context в data

    DataProcessing::SortPopular(data);
    // TODO из data в context

    return Next(context);
}
