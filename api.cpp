#include "api.h"
#include "user.h"
#include <string>
#include <algorithm>
#include "post.h"
#include "friend_request.h"
#include "user_report.h"
#include <iostream>

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
	cerr << "here3" << endl;
	current_user = user;
}

void Api::logout()
{
	if(current_user == NULL)
		throw NotLoggedIn();
	current_user = NULL;
}

void Api::sign_up(string username, string password, string name, string avatar_path)
{
	if(current_user != NULL)
		throw AlreadyLoggedIn();

	User* user = DB::instance()->get_user(username);
	if(user != NULL)
		throw UserExists();

	user = new User(username, password, name,avatar_path);
	DB::instance()->users.push_back(user);
	current_user = user;
}

string Api::get_avatar_path()
{
	return current_user->get_avatar_path();
}

string Api::get_username()
{
	return current_user->get_username();
}

vector<int> Api::get_latest_posts()
{
	vector<int> result;
	vector <Post*> all;
	for(int i = 0; i < current_user->friends.size(); i++)
	{
		vector <int> posts = current_user->friends[i]->get_latest_posts();
		for(int j = 0; j < posts.size(); j++)
		{
			Post* post = DB::instance()->get_post(posts[j]);
			all.push_back(post);
		}
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

void Api::post_photo(string title,string CDN_path, string hashtags, bool publicity)
{
	bool pub = publicity;
	if(current_user->is_admin())
		pub = true;
	
	Post* post = current_user->post_photo(title,CDN_path,hashtags,pub);
	DB::instance()->posts.push_back(post);
}

vector<int> Api::get_my_latest_posts()
{
	return current_user->get_latest_posts();
}

vector<int> Api::get_my_latest_liked_posts()
{
	return current_user->get_latest_liked_posts();
}

vector<string> Api::get_friends()
{
	return current_user->get_friends();
}

void Api::request_to_friend(string username)
{
	User* user = DB::instance()->get_user(username);
	if(user == current_user)
		throw FriendWithYourself();
	if(user == NULL)
		throw UserNotFound();
	if(current_user->has_requested_to(user))
		throw AlreadyRequested();
	if(current_user->is_friend_with(user))
		throw AlreadyFriends();

	FriendRequest* request = new FriendRequest(current_user,user);
	current_user->send_requests.push_back(request);
	user->received_requests.push_back(request);
}

void Api::approve_friend_request(int id)
{
	for(int i = 0; i < current_user->received_requests.size(); i++)
		if(current_user->received_requests[i]->id == id)
		{
			User* user = current_user->received_requests[i]->from;
			user->friend_request_approved(id);
			current_user->approve_friend_request(id);
			break;
		}
}

void Api::disapprove_friend_request(int id)
{
	for(int i = 0; i < current_user->received_requests.size(); i++)
	{
		if(current_user->received_requests[i]->id == id)
		{
			User* user = current_user->received_requests[i]->from;
			user->friend_request_disapproved(id);
			current_user->disapprove_friend_request(id);
			break;
		}
	}
}

void Api::remove_friend(string username)
{
	User* user = DB::instance()->get_user(username);
	if(user == NULL)
		throw UserNotFound();
	if(!current_user->is_friend_with(user))
		throw NotFriends();

	user->remove_friend(current_user);
	current_user->remove_friend(user);
}

void Api::report(string username)
{
	User* user = DB::instance()->get_user(username);
	if(user == NULL)
		throw UserNotFound();
	if(current_user->is_friend_with(user))
		throw AlreadyFriends();
	if(current_user->reported_before(user))
		throw ReportedBefore();

	UserReport* report = new UserReport(current_user,user);
	DB::instance()->reports.push_back(report);
	current_user->reports.push_back(report);
}

void Api::delete_user(string username)
{
	if(!current_user->is_admin())
		throw AccessDenied();
	
	User* user = DB::instance()->get_user(username);
	if(user == NULL)
		throw UserNotFound();
	if(user == current_user)
		throw AccessDenied();
}

void Api::like(int id)
{
	Post* post = DB::instance()->get_post(id);
	if(post == NULL)
		throw PostNotFound();
	if(current_user->has_liked(post))
		throw LikedBefore();
	
	current_user->liked_posts.push_back(post);
	post->liked_by.push_back(current_user);
}













