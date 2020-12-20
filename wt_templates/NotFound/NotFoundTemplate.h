#ifndef PROFORGIA_NOTFOUNDTEMPLATE_H
#define PROFORGIA_NOTFOUNDTEMPLATE_H


#include <BaseTemplate.h>

#define NOTFOUND_WAY "../wt_templates/templates/not_found.html"

class NotFoundTemplate : public BaseTemplate {
public:
    explicit NotFoundTemplate(Context& context);
    std::string & getHTML() override;

private:
    std::string notFoundHTML;
};


#endif //PROFORGIA_NOTFOUNDTEMPLATE_H
