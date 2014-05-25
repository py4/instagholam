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
	std::string get_content();
private:
	void remove_post_from_list(int);
	std::vector<Post*> posts;
	std::string content;
};
#endif
