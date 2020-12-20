//
// Created by sergei on 28.11.2020.
//

#include "PageUser.h"

PageManager::Status PageUser::get_profile_page(std::string& body) {

    // хз как будет в итоговом проекте
    // get_login_page();
//    std::string username = "cmorrec";
//    std::string ava = "ava_url";
//    Context::User user(username, ava);
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


    return CLIENT_ERROR_RIGHT;
}

PageManager::Status PageUser::get_room_page(std::string& body,std::string id) {
    return CLIENT_ERROR_RIGHT;
}

PageManager::Status PageUser::get_favorite_page(std::string& body) {
    return CLIENT_ERROR_RIGHT;
}

PageManager::Status PageUser::get_deadline_page(std::string& body) {
    return CLIENT_ERROR_RIGHT;
}

PageManager::Status PageUser::get_signup_page(std::string& body) {
    std::string page = "signup";
    Context context(page);
    TemplateWrapper view(context);
    body = view.getHTML();
    return OK;
}

PageManager::Status PageUser::get_login_page(std::string& body) {
    std::string page = "login";
    Context context(page);
    TemplateWrapper view(context);
    body = view.getHTML();
    return OK;
}

PageManager::Status PageUser::get_info_tags(std::string& body, std::string id_room, std::unique_ptr<std::vector<std::string>> tags) {
    return CLIENT_ERROR_RIGHT;
}

PageManager::Status PageUser::get_not_found(std::string& body) {
    std::string page = "not_found";
    Context context(page);
    TemplateWrapper view(context);
    body = view.getHTML();
    return OK;
}

PageManager::Status PageUser::get_server_err(std::string& body) {
    std::string page = "500";
    Context context(page);
    TemplateWrapper view(context);
    body = view.getHTML();
    return OK;
}
