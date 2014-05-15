#ifndef DB_H_
#define DB_H_

#include <vector>
#include <string>

class User;
class Post;
class HashTag;

class DB
{
	friend class Api;
public:
	User* get_user(std::string);
	static DB* instance();
	HashTag* find_or_create_hashtag(std::string);
private:
	std::vector <User*> users;
	//std::vector <Post*> posts;
	std::vector <HashTag*> hashtags;
	std::vector <User*> reported_users;

	DB();
	DB(DB const&);
	~DB();
	void operator=(DB const&);
	static DB* db;
};
#endif
