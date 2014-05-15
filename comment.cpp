#include "comment.h"
int Comment::count = 0;

Comment::Comment()
{
	id = count + 1;
	count++;
}
