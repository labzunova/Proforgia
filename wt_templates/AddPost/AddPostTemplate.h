#ifndef PROFORGIA_ADDPOSTTEMPLATE_H
#define PROFORGIA_ADDPOSTTEMPLATE_H

#include "NLTemplate.h"
#include "BaseTemplate.h"

#define ADD_POST_WAY "../wt_templates/templates/add_post.html"
#define ADD_POST_ROOM "add_post.room"
#define ADD_POST_FILE_UPLOAD_URL "add_post.file_upload_url"
#define ADD_POST_FILE_NAME_DB "add_post.file_name_db"

class AddPostTemplate : public BaseTemplate {
public:
    explicit AddPostTemplate(Context& context);
    std::string & getHTML() override;

private:
    std::string addPostHTML;
};


#endif //PROFORGIA_ADDPOSTTEMPLATE_H
