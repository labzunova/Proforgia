#ifndef PROFORGIA_CONTEXT_H
#define PROFORGIA_CONTEXT_H

struct Context {
    struct User {
        std::string username;
        std::string avatarUrl;

        User(std::string& username_, std::string& avatarUrl_) : username(username_), avatarUrl(avatarUrl_) {}
        User() {}
    };

    struct Room {
        std::string title;
        std::string url;

        Room(std::string& title_, std::string& url_) : title(title_), url(url_) {}

        Room() {}
    };

    struct Tag {

        std::string tag;
        std::string url;

        Tag(std::string& tag_, std::string& url_) : tag(tag_), url(url_) {}

        Tag() {}
    };

    struct Post {
        std::string title;
        std::string author;
        std::vector<Tag> tags;
        std::string text;
        std::vector<std::string> fileUrls;

        Post(std::string& title_,
             std::string& author_,
             std::vector<Tag>& tags_,
             std::string& text_,
             std::vector<std::string>& fileUrls_) : title(title_), author(author_), tags(tags_), text(text_),
                                                    fileUrls(fileUrls_) {}

        Post() {}
    };

    std::string page;

    explicit Context(std::string& page_) : page(page_) {}

    User user;
    std::vector<Room> rooms;

    void setProfileContext(User& user_, std::vector<Room>& rooms_) {
        user = user_;
        rooms = rooms_;
    }

    Room currentRoom;
    std::vector<Tag> tags;

    void setAddContext(User& user_, Room& currentRoom_, std::vector<Tag>& tags_) {
        user = user_;
        currentRoom = currentRoom_;
        tags = tags_;
    }

    std::vector<Post> posts;

    void setMainContext(User& user_, Room& currentRoom_, std::vector<Tag>& tags_, std::vector<Post>& posts_) {
        user = user_;
        currentRoom = currentRoom_;
        tags = tags_;
        posts = posts_;
    }

    Tag currentTag;

    void setTagContext(User& user_, Room& currentRoom_, std::vector<Tag>& tags_, std::vector<Post>& posts_,
                       Tag& tag_) {
        user = user_;
        currentRoom = currentRoom_;
        tags = tags_;
        posts = posts_;
        currentTag = tag_;
    }

};

#endif //PROFORGIA_CONTEXT_H
