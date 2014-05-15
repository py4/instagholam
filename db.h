#ifndef DB_H_
#define DB_H_

#include <vector>
#include <string>

class User;
class Post;
class HashTag;
class UserReport;

class DB
{
	friend class Api;
public:
	User* get_user(std::string);
	static DB* instance();
	HashTag* find_or_create_hashtag(std::string);
private:
	Post* get_post(int);
	bool is_reported(User*);
	std::vector <User*> users;
	std::vector <Post*> posts;
	std::vector <HashTag*> hashtags;
	std::vector <UserReport*> reports;

	DB();
	DB(DB const&);
	~DB();
	void operator=(DB const&);
	static DB* db;
};
#endif
