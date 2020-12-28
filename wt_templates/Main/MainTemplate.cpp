#include "MainTemplate.h"

#include <utility>

using namespace NL::Template;

MainTemplate::MainTemplate(Context& context) : BaseTemplate(context) {
    auto page = context.page;
    if (page == MAIN_PAGE)
        setTitle(MAIN_DEFAULT_TITLE);
    else if (page == TAG_PAGE)
        setTitle(context.currentTag.tag);
}

std::string& MainTemplate::getHTML() {
    LoaderFile loader;
    Template temp(loader);

    temp.load(MAIN_WAY);

    //---------------logged block--------------------
    setLoggedNavBar(temp);

    //---------------title  block--------------------
    temp.set(MAIN_TITLE, title);

    //---------------posts  block--------------------
    auto& block_posts = temp.block(MAIN_POSTS_BLOCK);
    block_posts.repeat(context.posts.size());
    for (int i = 0; i < context.posts.size(); i++) {
        block_posts[i].set(MAIN_POSTS_BLOCK_TITLE, context.posts[i].title);
        block_posts[i].set(MAIN_POSTS_BLOCK_AUTHOR, context.posts[i].author);
        block_posts[i].set(MAIN_POSTS_BLOCK_TEXT, context.posts[i].text);
        auto& block_files = block_posts[i].block(MAIN_POSTS_BLOCK_FILES_BLOCK);
        block_files.repeat(context.posts[i].files.size());
        for (int j = 0; j < context.posts[i].files.size(); j++) {
            if (context.posts[i].files[j].type == Context::File::IMAGE) {
                auto& block_file = block_files[j].block(MAIN_POSTS_BLOCK_FILES_BLOCK_IMG_BLOCK);
                block_files[j].block(MAIN_POSTS_BLOCK_FILES_BLOCK_FILE_BLOCK).disable();

                block_file.set(MAIN_POSTS_BLOCK_FILES_BLOCK_SRC, context.posts[i].files[j].url);
                block_file.set(MAIN_POSTS_BLOCK_FILES_BLOCK_NAME, context.posts[i].files[j].filename);
            } else {
                auto& block_file = block_files[j].block(MAIN_POSTS_BLOCK_FILES_BLOCK_FILE_BLOCK);
                block_files[j].block(MAIN_POSTS_BLOCK_FILES_BLOCK_IMG_BLOCK).disable();

                block_file.set(MAIN_POSTS_BLOCK_FILES_BLOCK_SRC, context.posts[i].files[j].url);
                block_file.set(MAIN_POSTS_BLOCK_FILES_BLOCK_NAME, context.posts[i].files[j].filename);
            }
        }

        auto& block_tags = block_posts[i].block(MAIN_POSTS_BLOCK_TAGS_BLOCK);
        block_tags.repeat(context.posts[i].tags.size());
        for (int j = 0; j < context.posts[i].tags.size(); j++) {
            block_tags[j].set(MAIN_POSTS_BLOCK_TAGS_BLOCK_NAME, context.posts[i].tags[j].tag);
            block_tags[j].set(MAIN_POSTS_BLOCK_TAGS_BLOCK_SRC, context.posts[i].tags[j].url);
            block_tags[j].set(MAIN_POSTS_BLOCK_TAGS_BLOCK_ROOM, context.currentRoom.url);
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