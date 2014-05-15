#include "post.h"
#include "parser.h"
#include "db.h"

using namespace std;
int Post::count = 0;

Post::Post(bool publicity)
{
	pub = publicity;
	set_current_time();
	set_id();
}

Post::Post(string title, bool publicity)
{
	pub = publicity;
	set_current_time();
	set_id();
	this->title = title;
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
