#include "user.h"
#include <string>
#include "friend_request.h"
#include "db.h"
#include "post.h"
#include "photo.h"
#include "comment.h"
using namespace std;

User::User()
{
}

User::User(string username, string password, string name)
{
	this->username = username;
	this->password = password;
	this->full_name = name;
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

vector <Post*> User::get_latest_posts()
{
	vector <Post*> result;
	
	for(int i = posts.size() - 1 - latest_count; i < posts.size(); i++)
		result.push_back(posts[i]);
	return result;
}

void User::post_photo(string title, string CDN_path, string hashtags)
{
	Post* new_post = new Post(title);
	new_post->set_hashtag(hashtags);
	Photo* photo = new Photo(CDN_path);
	//DB::posts.push_back(photo);
}

