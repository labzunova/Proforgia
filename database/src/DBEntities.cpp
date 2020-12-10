#include "../include/Utils/DBEntities.h"

#include <utility>
#include "../include/DataManager.h"


shared_ptr<DBUser> DBUser::get(int _id, ErrorCodes &error) {
    return DataManager::getInstance().get_user_info(_id, error);
}

shared_ptr<DBUser> DBUser::get(std::string _nickname, ErrorCodes &error) {
    return DataManager::getInstance().get_user_info(_nickname, error);
}

bool DBUser::add(DBUser::User _user, ErrorCodes &error) {
    return DataManager::getInstance().add_user(_user, error);
}

bool DBUser::remove(int id, ErrorCodes &error) {
    return DataManager::getInstance().remove_user(id, error);
}

bool DBUser::update(ErrorCodes &error) {
    return DataManager::getInstance().edit_user(id, User(nick_name, email, password), error);
}

std::optional< vector<pair<DBRoom, Rights>> > DBUser::get_rooms(ErrorCodes &error) {
    return DataManager::getInstance().get_user_rooms(id, error);
}

const string &DBUser::getPassword() const {
    return password;
}




// TODO: дописать псевдокод и сделать рабочий метод
std::vector<std::string> DBPost::get_attachments(ErrorCodes &error) {

}

std::optional< vector<DBPost> > DBPost::get(std::vector<std::string> _tags, int room_id, ErrorCodes &error) {
	// get all posts, that contain all tags in _tags
    return DataManager::getInstance().get_posts_by_tags(_tags, room_id, error);
}

shared_ptr<DBPost> DBPost::get(int _id, ErrorCodes &error) {
    return DataManager::getInstance().get_post_info(_id, error);
}

bool DBPost::add(const DBPost::Post& _post, ErrorCodes &error) {
    return DataManager::getInstance().add_post(_post, error);
}

bool DBPost::remove(int id, ErrorCodes &error) {
    return DataManager::getInstance().remove_post(id, error);
}

bool DBPost::update(ErrorCodes &error) {
    return DataManager::getInstance().edit_post(id, Post(room_id, user_id, title, text), error);
}

bool DBPost::update_tags(vector<string> new_tags, ErrorCodes &error) {
    return DataManager::getInstance().add_tags_to_post(new_tags, id, room_id, error);
}

string DBPost::get_upload_link(ErrorCodes &error) {

}

bool DBPost::add_file(string filename, ErrorCodes &error) {

}

bool DBPost::remove_file(string filename, ErrorCodes &error) {

}

DBRoom DBPost::get_room(ErrorCodes &error) {

}

DBUser DBPost::get_author(ErrorCodes &error) {

}

std::vector<DBTag> DBPost::get_tags(ErrorCodes &error) {

}

// Это не надо, сережа реализует у себя!
std::vector<DBTag> get_associated_tags(std::vector<std::string>& _tags, ErrorCodes &error) {
	// get all posts, that contain all tags in _tags
	// get all tags, from every post that was found
	// sort tags by popularity (via unordered map?)
	// return tags in sorted order
}

DBEntity::DBEntity(int& _id) : id(_id) {}

int DBEntity::get_id() const {
    return id;
}

shared_ptr<DBRoom> DBRoom::get(int _id, ErrorCodes &error) {
    return DataManager::getInstance().get_room_info(_id, error);
}

bool DBRoom::add(DBRoom::Room _room, ErrorCodes &error) {
    return DataManager::getInstance().add_room(_room, error);
}

bool DBRoom::remove(int id, ErrorCodes &error) {
    return DataManager::getInstance().remove_room(id, error);
}

bool DBRoom::add_user(const int &room_id, const int &user_id, Rights user_rights, ErrorCodes &error) {
    return DataManager::getInstance().add_user_to_room(room_id, user_id, user_rights, error);
}

bool DBRoom::remove_user(const int &room_id, const int &user_id, ErrorCodes &error) {
    return DataManager::getInstance().remove_user_from_room(room_id, user_id, error);
}

bool DBRoom::update(ErrorCodes &error) {
    return DataManager::getInstance().edit_room(id, Room(room_name, description), error);
}

std::optional< vector<pair<DBUser, Rights>> > DBRoom::get_users(ErrorCodes &error) {
    return DataManager::getInstance().get_room_users(id, error);
}

std::optional< std::vector<DBPost> > DBRoom::get_posts(ErrorCodes &error) {
    return DataManager::getInstance().get_room_posts(id, error);
}

std::optional< std::vector<DBTag> > DBRoom::get_tags(ErrorCodes &error) {
    return DataManager::getInstance().get_room_tags(id, error);
}

DBTag::Tag::Tag(string name, int roomId) : name(std::move(name)), room_id(roomId) {}

DBTag::DBTag(int &id, string name, int roomId) : DBEntity(id), name(std::move(name)),
                                                                         room_id(roomId) {}

bool DBTag::update(ErrorCodes &error) {
    return false;
}

DBPost::Post::Post(int roomId, int userId, const string &title, const string &text) : room_id(roomId), user_id(userId),
                                                                                      title(title), text(text) {}
