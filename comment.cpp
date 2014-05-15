#include "comment.h"
#include "post.h"

int Comment::count = 0;

Comment::Comment()
{
	id = count + 1;
	count++;
}

int Comment::get_post_id()
{
	return post->get_id();
}
