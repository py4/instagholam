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
	friend class Core;
public:
	User* get_user(std::string);
	static DB* instance();
	HashTag* find_or_create_hashtag(std::string);
	void free_db();
private:
	Post* get_post(int);
	bool is_reported(User*);
	std::vector <User*> users;
	std::vector <Post*> posts;
	std::vector <HashTag*> hashtags;
	std::vector <UserReport*> reports;

	DB();
	~DB();
	DB(DB const&);
	void operator=(DB const&);
	static DB* db;
};
#endif