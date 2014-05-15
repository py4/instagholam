#include "api.h"
#include "user.h"
#include <string>
#include <algorithm>
#include "post.h"
using namespace std;

Api::Api()
{
	current_user = NULL;
}

void Api::login(string username, string password)
{
	if(current_user != NULL)
		throw AlreadyLoggedIn();
	User* user = DB::instance()->get_user(username);
	if(user == NULL)
		throw UserNotFound();
	if(user->password != password)
		throw WrongCredentials();
	current_user = user;
}

void Api::logout()
{
	if(current_user == NULL)
		throw NotLoggedIn();
	current_user = NULL;
}

void Api::sign_up(string username, string password, string name)
{
	if(current_user != NULL)
		throw AlreadyLoggedIn();

	User* user = DB::instance()->get_user(username);
	if(user != NULL)
		throw UserExists();

	user = new User(username, password, name);
	DB::instance()->users.push_back(user);
}

vector<int> Api::get_latest_posts()
{
	if(current_user != NULL)
		throw AccessDenied();

	vector<int> result;
	vector <Post*> all;
	for(int i = 0; i < current_user->friends.size(); i++)
	{
		vector <Post*> posts = current_user->friends[i]->get_latest_posts();
		for(int j = 0; j < posts.size(); j++)
			all.push_back(posts[j]);
	}
	sort(all.begin(), all.end(), compare_post_time);

	for(int i = 0; i < 5; i++)
	{
		if(all.size() - 1 - i >= 0)
			result.push_back(all[i]->id);
		else
			break;
	}
	return result;
}

bool Api::compare_time(time_t& first, time_t& second)
{
	return difftime(first,second) > 0;
}

bool Api::compare_post_time(Post* post1, Post* post2)
{
	return compare_time(post1->created_at, post2->created_at);
}

void Api::post_photo(string title,string CDN_path, string hashtags)
{
	current_user->post_photo(title,CDN_path,hashtags);
}


