#ifndef DB_H_
#define DB_H_

#include <vector>
#include <string>
#include "cvector.h"

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
	cvector<User*> users;
	cvector<Post*> posts;
	cvector<HashTag*> hashtags;
	cvector<UserReport*> reports;

	DB();
	~DB();
	DB(DB const&);
	void operator=(DB const&);
	static DB* db;
};
#endif
