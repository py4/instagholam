#ifndef POST_H_
#define POST_H_

#include <string>
#include <vector>
#include <ctime>

class User;
class Photo;
class Comment;
class HashTag;

class Post
{
	friend class DB;
	friend class Api;
public:
	Post(bool = false);
	Post(std::string, bool = false);
	Post(std::string, bool, std::string, Photo*, User*);
	void set_time(time_t&);
	void set_title(std::string);
	void set_current_time();
	void set_hashtag(std::string);
	void set_photo(Photo*);
	int get_id();
	std::string get_created_at();
	bool is_pub() { return pub; }
	User* get_user() { return user; }
	std::string get_path();
private:
	void set_id();
	int id;
	bool pub;
	Photo* photo;
	User* user;
	std::string title;
	std::vector<Comment*> comments;
	std::vector<HashTag*> hashtags;
	std::vector<User*> liked_by;
	time_t created_at;
	static int count;
};
#endif
