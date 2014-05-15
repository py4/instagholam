#ifndef FRIEND_REQUEST_H_
#define FRIEND_REQUEST_H_

class User;

class FriendRequest
{
public:
	FriendRequest();
private:
	int id;
	User* from;
	User* to;
	static int count;
};
#endif
