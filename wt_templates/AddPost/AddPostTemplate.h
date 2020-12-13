#ifndef PROFORGIA_ADDPOSTTEMPLATE_H
#define PROFORGIA_ADDPOSTTEMPLATE_H

#include "NLTemplate.h"
#include "BaseTemplate.h"

class AddPostTemplate : public BaseTemplate {
public:
    explicit AddPostTemplate(Context& context);
    std::string & getHTML() override;

private:
    std::string addPostHTML;
};


#endif //PROFORGIA_ADDPOSTTEMPLATE_H
