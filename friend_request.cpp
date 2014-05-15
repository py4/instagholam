#include "friend_request.h"
int FriendRequest::count = 0;

FriendRequest::FriendRequest()
{
	set_id();
}

FriendRequest::FriendRequest(User* from, User* to)
{
	set_id();
	this->from = from;
	this->to = to;
}

void FriendRequest::set_id()
{
	count++;
	id = count;
}

int FriendRequest::get_id()
{
	return id;
}

User* FriendRequest::get_from()
{
	return from;
}

User* FriendRequest::get_to()
{
	return to;
}
