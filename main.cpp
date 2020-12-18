#include <iostream>
#include "wt_templates/TemplateWrapper.h"

int main(int argc, char* argv[]) {
    std::string username = "cmorrec";
    std::string ava = "ava_url";
    Context::User user(username, ava);

//    std::string page_value = "login";
//    Context context(page_value);

    std::string page_value = "not_found";
    Context context(page_value);

//    std::string page_value = "signup";
//    Context context(page_value);

//    std::string page_value = "profile";
//    std::string title = "title";
//    std::string url = "url";
//    std::vector<Context::Room> rooms = {Context::Room(title, url),
//                                        Context::Room(title, url)};
//    Context context(page_value);
//    context.setProfileContext(user, rooms);

//    std::string page_value = "add";
//    std::string title = "title";
//    std::string tag = "tag";
//    std::string url = "url";
//    Context::Room room(title, url);
//    std::vector<Context::Tag> tags = {Context::Tag(tag, url),
//                                      Context::Tag(tag, url)};
//    Context context(page_value);
//    context.setAddContext(user, room, tags);

//    std::string page_value = "main";
//    std::string title = "title";
//    std::string author = "author";
//    std::string text = "text";
//    std::string tag = "tag";
//    std::string url = "url";
//    std::vector<std::string> urls = {"url1", "url2"};
//    Context::Room room(title, url);
//    std::vector<Context::Tag> tags = {Context::Tag(tag, url),
//                                      Context::Tag(tag, url)};
//    std::vector<Context::Post> posts = {Context::Post(title, author, tags, text, urls),
//                                        Context::Post(title, author, tags, text, urls)};
//    Context context(page_value);
//    context.setMainContext(user, room, tags, posts);

//    std::string page_value = "tag";
//    std::string title = "title";
//    std::string author = "author";
//    std::string text = "text";
//    std::string tag = "tag";
//    std::string url = "url";
//    std::vector<std::string> urls = {"url1", "url2"};
//    Context::Room room(title, url);
//    std::vector<Context::Tag> tags = {Context::Tag(tag, url),
//                                      Context::Tag(tag, url)};
//    std::vector<Context::Post> posts = {Context::Post(title, author, tags, text, urls),
//                                        Context::Post(title, author, tags, text, urls)};
//    Context::Tag currentTag(tag, url);
//    Context context(page_value);
//    context.setTagContext(user, room, tags, posts, currentTag);

    std::cout << TemplateWrapper(context).getHTML();
    return 0;
}
