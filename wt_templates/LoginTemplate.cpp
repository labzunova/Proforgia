#include "LoginTemplate.h"

LoginTemplate::LoginTemplate() : Wt::WTemplate(tr("tpl.template")) {
    addFunction("tr", &WTemplate::Functions::tr);
    auto edit = bindWidget("edit", Wt::cpp14::make_unique<Wt::WLineEdit>());
    auto btn = bindNew<Wt::WPushButton>("btn", tr("str.greet-me"));
    bindEmpty("result");
    auto showGreeting = [this]{
        auto edit = resolve<Wt::WLineEdit*>("edit");
        bindString("result",
                   tr("str.result").arg(edit->text()),
                   Wt::TextFormat::Plain);
    };
    edit->enterPressed().connect(showGreeting);
    btn->clicked().connect(showGreeting);
}

Wt::WString LoginTemplate::getTemplateText() {
    return this->templateText();
}