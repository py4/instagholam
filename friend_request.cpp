#include "friend_request.h"

int FriendRequest::count = 0;

FriendRequest::FriendRequest()
{
	count++;
	id = count;
}
