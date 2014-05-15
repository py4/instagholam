#include "user.h"
#include <string>
#include "friend_request.h"
#include "db.h"
#include "post.h"
#include "photo.h"
#include "comment.h"
#include "user_report.h"

using namespace std;

User::User()
{
}

User::User(string username, string password, string name, string avatar_path)
{
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
}

bool User::is_admin()
{
	return username == "admin";
}

vector <int> User::get_latest_posts()
{
	vector <int> result;
	
	for(int i = posts.size() - 1 - latest_count; i < posts.size() and i > 0; i++)
		result.push_back(posts[i]->get_id());
	
	return result;
}

vector <int> User::get_latest_liked_posts()
{
	vector <int> result;
	for(int i = liked_posts.size() - 1 - latest_count; i < liked_posts.size() and i > 0; i++)
		result.push_back(liked_posts[i]->get_id());
	return result;
}

Post* User::post_photo(string title, string CDN_path, string hashtags, bool publicity)
{
	Post* new_post = new Post(title,publicity);
	new_post->set_hashtag(hashtags);
	Photo* photo = new Photo(CDN_path);
	new_post->set_photo(photo);
	return new_post;
	//DB::posts.push_back(photo);
}

string User::get_username()
{
	return username;
}

string User::get_full_name()
{
	return full_name;
}

vector<string> User::get_friends()
{
	vector<string> result;
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


	

