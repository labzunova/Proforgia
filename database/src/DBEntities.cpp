#include "../include/Utils/DBEntities.h"

#include <utility>
#include <ctime>
#include <unistd.h>
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

string gen_random(const int len) {

    string tmp_s;
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

    srand( (unsigned) time(nullptr) * getpid());

    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i)
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];


    return tmp_s;
}

string DBPost::get_upload_link(int post_id, ErrorCodes &error) {
    // пока имя файла в ссылке генерируется рандомно, как вариант можно заменять в процессе
    string filename = gen_random(10);
    string storage_file_path = POSTS_TABLE_NAME + "/" + std::to_string(post_id) + "/" + filename;

    return DataManager::getInstance().get_file_upload_link(storage_file_path, error);
}

bool DBPost::add_file_to_db(string filename, ErrorCodes &error) {
    // добавить запись о файле в БД

}

bool DBPost::remove_file(string filename, ErrorCodes &error) {
    DataManager::getInstance().remove_file_from_storage(filename, error);
    // TODO: remove from db
    assert(false);
}

shared_ptr<DBRoom> DBPost::get_room(ErrorCodes &error) {
    return DBRoom::get(room_id, error);
}

shared_ptr<DBUser> DBPost::get_author(ErrorCodes &error) {
    return DBUser::get(user_id, error);
}

std::optional< std::vector<DBTag> > DBPost::get_tags(ErrorCodes &error) {
    return DataManager::getInstance().get_post_tags(id, error);
}

std::optional< std::vector<std::string> > DBPost::get_attachments(ErrorCodes &error) {
    return DataManager::getInstance().get_post_attachments(id, error);
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

shared_ptr<DBTag> DBTag::get(int _id, ErrorCodes &error) {
    return DataManager::getInstance().get_tag_info(_id, error);
}

const string &DBTag::getName() const {
    return name;
}

int DBTag::getRoomId() const {
    return room_id;
}

DBPost::Post::Post(int roomId, int userId, const string &title, const string &text) : room_id(roomId), user_id(userId),
                                                                                      title(title), text(text) {}

DBSession::Session::Session(const string sessionId, int userId) : session_identificator(sessionId), user_id(userId) {}

DBSession::DBSession(int &id, const local_date_time &creationDate, const string &sessionId, int userId)
        : DBEntity(id), creation_date(creationDate), session_identificator(sessionId), user_id(userId) {}

shared_ptr<DBSession> DBSession::get(int _id, ErrorCodes &error) {
    return DataManager::getInstance().get_session_info(_id, error);
}

bool DBSession::remove(int id, ErrorCodes &error) {
    return DataManager::getInstance().remove_session(id, error);
}

bool DBSession::add(DBSession::Session _session, ErrorCodes &error) {
    return DataManager::getInstance().add_session(_session, error);
}

bool DBSession::update(ErrorCodes &error) {
    return false;
}

shared_ptr<DBUser> DBSession::get_user(ErrorCodes &error) {
    return DBUser::get(user_id, error);
}

const local_date_time &DBSession::getCreationDate() const {
    return creation_date;
}

const string &DBSession::getSessionIdentificator() const {
    return session_identificator;
}

int DBSession::getUserId() const {
    return user_id;
}
