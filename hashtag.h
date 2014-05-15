#ifndef HASHTAG_H_
#define HASHTAG_H_

#include <string>
#include <vector>
class Post;

class HashTag
{
	friend class DB;
public:
	HashTag();
	HashTag(std::string);
private:
	std::vector<Post*> posts;
	std::string content;
};
#endif
