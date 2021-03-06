#include "user.h"
#include <string>
#include "friend_request.h"
#include "db.h"
#include "post.h"
#include "photo.h"
#include "comment.h"
#include "user_report.h"
#include <iostream>
using namespace std;

User::User()
{
	avatar = NULL;
}

User::User(string username, string password, string name, string avatar_path)
{
	avatar = NULL;
	this->username = username;
	this->password = password;
	this->full_name = name;
	avatar = new Photo(avatar_path);
}

User::~User()
{
	for(int i = 0; i < posts.size(); i++)
		delete posts[i];
	for(int i = 0; i < comments.size(); i++)
		delete comments[i];
	for(int i = 0; i < send_requests.size(); i++)
		delete send_requests[i];
	delete avatar;
}

bool User::is_admin()
{
	return username == "admin";
}

string User::get_avatar_path()
{
	return avatar->get_path();
}

cvector <int> User::get_latest_posts()
{
	cvector <int> result;
	//for(int i = posts.size() - 1; posts.size() - i <= latest_count and i >= 0; i--)
	for(int i = posts.size() - 1; i >= 0; i--)
		result.push_back(posts[i]->get_id());
	return result;
}

cvector <int> User::get_public_posts()
{
	cvector<int> result;
	for(int i = posts.size() - 1; i >= 0; i--)
		if(posts[i]->is_pub())
			result.push_back(posts[i]->get_id());
		else
			continue;
	return result;
}

cvector <Post*> User::get_latest_posts_full()
{
	cvector <Post*> result;
	for(int i = posts.size() - 1; i >= 0; i--)
		result.push_back(posts[i]);
	return result;
}

cvector <int> User::get_latest_liked_posts()
{
	cvector <int> result;
	//for(int i = liked_posts.size() - 1; liked_posts.size() - i < latest_count and i > 0; i++)
	for(int i = liked_posts.size() - 1; i >= 0; i--)
		result.push_back(liked_posts[i]->get_id());
	return result;
}

Post* User::post_photo(string title, string CDN_path, string hashtags, bool publicity)
{
	Photo* photo = new Photo(CDN_path);
	Post* new_post = new Post(title,publicity,hashtags,photo,this);
	posts.push_back(new_post);
	return new_post;
}

string User::get_username()
{
	return username;
}

string User::get_full_name()
{
	return full_name;
}

cvector<string> User::get_friends()
{
	cvector<string> result;
	for(int i = 0; i < friends.size(); i++)
		result.push_back(friends[i]->get_username());
	
	return result;
}

bool User::has_requested_to(User* user)
{
	for(int i = 0; i < send_requests.size(); i++)
		if(send_requests[i]->get_to() == user)
			return true;
	return false;
}

bool User::is_friend_with(User* user)
{
	for(int i = 0; i < friends.size(); i++)
		if(friends[i] == user)
			return true;
	return false;
}

bool User::able_to_see(Post* post)
{
	if(post->is_pub())
		return true;

	User* user = post->get_user();
	if(user != this and !user->is_friend_with(this))
		return false;
	return true;
}


/*void User::remove_friend(User* user)
{
	for(int i = 0; i < friends.size(); i++)
		if(friends[i] == user)
		{
			friends.erase(friends.begin()
		}
		}*/

void User::approve_friend_request(int id)
{
	for(int i = 0; i < received_requests.size(); i++)
		if(received_requests[i]->get_id() == id)
		{
			User* user = received_requests[i]->get_from();
			friends.push_back(user);
			received_requests.erase(received_requests.begin() + i);
			break;
		}
}

void User::disapprove_friend_request(int id)
{
	for(int i = 0; i < received_requests.size(); i++)
		if(received_requests[i]->get_id() == id)
		{
			received_requests.erase(received_requests.begin() + i);
			break;
		}
}

void User::friend_request_approved(int id)
{
	for(int i = 0; i < send_requests.size(); i++)
		if(send_requests[i]->get_id() == id)
		{
			User* user = send_requests[i]->get_to();
			friends.push_back(user);
			send_requests.erase(send_requests.begin() + i);
			break;
		}
}

void User::friend_request_disapproved(int id)
{
	for(int i = 0; i < send_requests.size(); i++)
		if(send_requests[i]->get_id() == id)
		{
			send_requests.erase(send_requests.begin() + i);
			break;
		}
	
}
//TODO exception in lib or in models?
void User::remove_friend(User* user)
{
	for(int i = 0; i < friends.size(); i++)
		if(friends[i] == user)
		{
			friends.erase(friends.begin() + i);
			return;
		}
}

bool User::reported_before(User* user)
{
	for(int i = 0; i < reports.size(); i++)
		if(reports[i]->get_to() == user)
			return true;
	return false;
}

void User::remove_comment_on_post(int id)
{
	for(int i = 0; i < comments.size(); i++)
		if(comments[i]->get_post_id() == id)
		{
			Comment* comment = comments[i];
			comments.erase(comments.begin() + i);
			delete comment;
			break;
		}
}

void User::remove_liked_post(int id)
{
	for(int i = 0; i < liked_posts.size(); i++)
		if(liked_posts[i]->get_id() == id)
		{
			liked_posts.erase(liked_posts.begin() + i);
			break;
		}
}

bool User::has_liked(Post* post)
{
	for(int i = 0; i < liked_posts.size(); i++)
		if(liked_posts[i] == post)
			return true;
	return false;
}

Comment* User::get_comment(int id)
{
	for(int i = 0; i < comments.size(); i++)
		if(comments[i]->get_id() == id)
			return comments[i];
	return NULL;
}


	

