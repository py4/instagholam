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
	void set_time(time_t&);
	void set_title(std::string);
	void set_current_time();
	void set_hashtag(std::string);
private:
	void set_id();
	int id;
	bool pub;
	Photo* photo;
	std::string title;
	std::vector<Comment*> comments;
	std::vector<HashTag*> hashtags;
	std::vector<User*> liked_by;
	time_t created_at;
	static int count;
};
#endif
