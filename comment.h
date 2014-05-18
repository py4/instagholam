#ifndef COMMENT_H_
#define COMMENT_H_

#include <ctime>
#include <string>
class Post;
class User;

class Comment
{
	friend class Api;
public:
	Comment();
	Comment(std::string);
	Comment(User*,Post*,std::string);
	int get_post_id();
	int get_id() { return id; }
	std::string get_user();
	std::string get_content();
	std::string get_created_at();
private:
	int id;
	Post* post;
	User* user;
	std::time_t created_at;
	static int count;
	std::string content;
};
#endif
