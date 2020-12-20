#ifndef PROFORGIA_MAINTEMPLATE_H
#define PROFORGIA_MAINTEMPLATE_H

#include "NLTemplate.h"
#include "BaseTemplate.h"

#define MAIN_WAY "../wt_templates/templates/main.html"

#define MAIN_TITLE "main_title"
#define MAIN_DEFAULT_TITLE "Last posts"
#define MAIN_POSTS_BLOCK "posts_block"
#define MAIN_POSTS_BLOCK_TITLE "post.title"
#define MAIN_POSTS_BLOCK_TEXT "post.text"
#define MAIN_POSTS_BLOCK_AUTHOR "post.author"
#define MAIN_POSTS_BLOCK_FILES_BLOCK "post.files"
#define MAIN_POSTS_BLOCK_FILES_BLOCK_NAME "file.name"
#define MAIN_POSTS_BLOCK_FILES_BLOCK_SRC "file.url"
#define MAIN_POSTS_BLOCK_TAGS_BLOCK "post.tags"
#define MAIN_POSTS_BLOCK_TAGS_BLOCK_NAME "tag"
#define MAIN_POSTS_BLOCK_TAGS_BLOCK_SRC "tag.url"
#define MAIN_POSTS_BLOCK_TAGS_BLOCK_ROOM "room.url"

class MainTemplate : public BaseTemplate {
public:
    explicit MainTemplate(Context& context);

    std::string& getHTML() override;

protected:
    void setTitle(std::string title);

private:
    std::string mainHTML;
    std::string title;

    struct Post {
        std::string title;
        std::string author;
        std::vector<std::string> tags;

        Post(std::string& title,
        std::string& author,
        std::vector<std::string>& tags) : title(title), author(author), tags(tags) {}
    };
};



#endif //PROFORGIA_MAINTEMPLATE_H
