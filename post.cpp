#include "post.h"
#include "parser.h"
#include "db.h"
#include "photo.h"
#include "comment.h"
using namespace std;
int Post::count = 0;

Post::Post(bool publicity)
{
	pub = publicity;
	set_current_time();
	set_id();
	user = NULL;
}

Post::Post(string title, bool publicity)
{
	pub = publicity;
	set_current_time();
	set_id();
	this->title = title;
	user = NULL;
}

Post::Post(string title, bool publicity, string hashtags, Photo* photo, User* user)
{
	pub = publicity;
	set_current_time();
	set_id();
	this->title = title;
	set_hashtag(hashtags);
	this->photo = photo;
	this->user = user;
}

void Post::set_time(time_t& time)
{
	created_at = time;
}

void Post::set_title(string title)
{
	this->title = title;
}

void Post::set_current_time()
{
	time_t timer;
	time(&timer);
	created_at = timer;
}

void Post::set_hashtag(string line)
{
	vector<string> tags = get_hashtags(line);
	for(int i = 0; i < tags.size(); i++)
	{
		HashTag* hashtag = DB::instance()->find_or_create_hashtag(tags[i]);
		hashtags.push_back(hashtag);
	}
}

void Post::set_id()
{
	id = count + 1;
	count++;
}

void Post::set_photo(Photo* photo)
{
	this->photo = photo;
}

int Post::get_id()
{
	return id;
}

string Post::get_created_at()
{
	struct tm * ptr;
    char buf [20];
    ptr = localtime(&created_at);
    strftime (buf,20,"%x",ptr);
    return buf;
}

string Post::get_path()
{
	return photo->get_path();
}

Comment* Post::get_comment(int id)
{
	for(int i = 0; i < comments.size(); i++)
		if(comments[i]->get_id() == id)
			return comments[i];
	return NULL;
}