#include "hashtag.h"
#include "post.h"
using namespace std;
HashTag::HashTag()
{
}

HashTag::HashTag(string content)
{
	this->content = content;
}

void HashTag::remove_post_from_list(int id)
{
	for(int i = 0; i < posts.size(); i++)
		if(posts[i]->get_id() == id)
		{
			posts.erase(posts.begin() + i);
			break;
		}
}
