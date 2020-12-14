#include "MainTemplate.h"

#include <utility>

using namespace NL::Template;

MainTemplate::MainTemplate(Context& context) : BaseTemplate(context) {
    auto page = context.page;
    if (page == "main")
        setTitle("Last posts");
    else if (page == "tag")
        setTitle(context.currentTag.tag);
}

std::string& MainTemplate::getHTML() {
    LoaderFile loader;
    Template temp(loader);

    temp.load("../wt_templates/templates/main.html");

    //---------------logged block--------------------
    setLoggedNavBar(temp);

    //---------------title  block--------------------
    temp.set("main_title", title);

    //---------------posts  block--------------------
    auto& block_posts = temp.block("posts_block");
    block_posts.repeat(context.posts.size());
    for (int i = 0; i < context.posts.size(); i++) {
        block_posts[i].set("post.title", context.posts[i].title);
        block_posts[i].set("post.author", context.posts[i].author);
        auto& block_tags = block_posts[i].block("post.tags");
        block_tags.repeat(context.posts[i].tags.size());
        for (int j = 0; j < context.posts[i].tags.size(); j++) {
            block_tags[j].set("tag", context.posts[i].tags[j].tag);
            block_tags[j].set("tag.url", context.posts[i].tags[j].url);
        }
    }

    //---------------right  block--------------------
    setRightBlock(temp);

    std::stringstream os;
    temp.render(os);
    mainHTML = os.str();
    return mainHTML;
}

void MainTemplate::setTitle(std::string title_) {
    title = std::move(title_);
}