#ifndef PROFORGIA_PROFILETEMPLATE_H
#define PROFORGIA_PROFILETEMPLATE_H

#include "NLTemplate.h"
#include "BaseTemplate.h"

class ProfileTemplate : public BaseTemplate {
public:
    explicit ProfileTemplate(Context& context);

    std::string& getHTML() override;

private:
    std::string profileHTML;
};


#endif //PROFORGIA_PROFILETEMPLATE_H
