#ifndef PROFORGIA_NOTFOUNDTEMPLATE_H
#define PROFORGIA_NOTFOUNDTEMPLATE_H


#include <BaseTemplate.h>

class NotFoundTemplate : public BaseTemplate {
public:
    explicit NotFoundTemplate(Context& context);
    std::string & getHTML() override;

private:
    std::string notFoundHTML;
};


#endif //PROFORGIA_NOTFOUNDTEMPLATE_H
