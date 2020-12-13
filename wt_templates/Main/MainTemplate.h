#ifndef PROFORGIA_MAINTEMPLATE_H
#define PROFORGIA_MAINTEMPLATE_H

#include "NLTemplate.h"
#include "BaseTemplate.h"

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
