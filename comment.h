#ifndef COMMENT_H_
#define COMMENT_H_

#include <ctime>

class Post;
class User;

class Comment
{
public:
	Comment();
private:
	int id;
	Post* post;
	User* user;
	std::time_t created_at;
	static int count;
};
#endif
