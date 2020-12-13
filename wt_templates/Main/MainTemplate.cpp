#include "MainTemplate.h"

#include <utility>

using namespace NL::Template;

MainTemplate::MainTemplate(Context& context) : BaseTemplate(context) {
    auto page = context.at("page");
    if (page == "main")
        setTitle("Last posts");
    else if (page == "tag")
        setTitle("Tag: interesting tag");
}

std::string& MainTemplate::getHTML() {
    LoaderFile loader;
    Template temp(loader);

    temp.load("../wt_templates/templates/main.html");

    //---------------logged block--------------------
    std::string username = "cmorrec";
    auto& block_logged = temp.block("logged_block");
    block_logged.set("username", username);
    block_logged.set("avatar_res", "aaaaaaaaaaaaaaaaavvvvvvvvvvvvvaaaaaaaaaaaaaa");

    //---------------title_  block--------------------
    temp.set("main_title", title);

    //---------------posts  block--------------------
    std::string title_ = "title";
    std::string author = "author";
    std::vector<std::string> tags = {"tag1", "tag2"};
    std::vector<Post> posts = {Post(title_, author, tags), Post(title_, author, tags)};
    auto& block_posts = temp.block("posts_block");
    block_posts.repeat(posts.size());
    for (int i = 0; i < posts.size(); i++) {
        block_posts[i].set("post.title", posts[i].title);
        block_posts[i].set("post.author", posts[i].author);
        auto& block_tags = block_posts[i].block("post.tags");
        block_tags.repeat(posts[i].tags.size());
        for (int j = 0; j < posts[i].tags.size(); j++)
            block_tags[j].set("tag", posts[i].tags[j]);
    }

    //---------------right  block--------------------
    std::vector<std::string> right_tags = {"Термодед", "Случайный дед", "ОБЖ", "Стройсмех", "Базы данных"};
    auto& block_right = temp.block("right_block.tags");
    block_right.repeat(right_tags.size());
    for (int i = 0; i < right_tags.size(); i++)
        block_right[i].set("tag", right_tags[i]);

    std::stringstream os;
    temp.render(os);
    mainHTML = os.str();
    return mainHTML;
}

void MainTemplate::setTitle(std::string title_) {
    title = std::move(title_);
}