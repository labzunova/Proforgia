#ifndef PROFORGIA_ADDPOSTTEMPLATE_H
#define PROFORGIA_ADDPOSTTEMPLATE_H

#include "NLTemplate.h"
#include "BaseTemplate.h"

#define ADD_POST_WAY "../wt_templates/templates/add_post.html"
#define ADD_POST_ROOM "add_post.room"

class AddPostTemplate : public BaseTemplate {
public:
    explicit AddPostTemplate(Context& context);
    std::string & getHTML() override;

private:
    std::string addPostHTML;
};


#endif //PROFORGIA_ADDPOSTTEMPLATE_H
