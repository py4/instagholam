#include "db.h"
#include "user.h"
#include "post.h"
#include "hashtag.h"
#include <string>
#include "friend_request.h"
#include "user_report.h"
using namespace std;

DB* DB::db = NULL;

DB::DB()
{
}

DB* DB::instance()
{
	if(db == NULL)
	{
		db = new DB;
		return db;
	}
	return db;
}

DB::~DB()
{
	for(int i = 0; i < users.size(); i++)
		delete users[i];
	//for(int i = 0; i < posts.size(); i++)
	//delete posts[i];
	for(int i = 0; i < hashtags.size(); i++)
		delete hashtags[i];
	for(int i = 0; i < reports.size(); i++)
		delete reports[i];
}

User* DB::get_user(string username)
{
	for(int i = 0; i < users.size(); i++)
		if(users[i]->username == username)
			return users[i];
	return NULL;
}

HashTag* DB::find_or_create_hashtag(string content)
{
	for(int i = 0; i < hashtags.size(); i++)
		if(hashtags[i]->content == content)
			return hashtags[i];
	HashTag* hashtag = new HashTag(content);
	hashtags.push_back(hashtag);
	return hashtag;
}

Post* DB::get_post(int id)
{
	for(int i = 0; i < posts.size(); i++)
		if(posts[i]->id == id)
			return posts[i];
	return NULL;
}
