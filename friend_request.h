#ifndef FRIEND_REQUEST_H_
#define FRIEND_REQUEST_H_

class User;

class FriendRequest
{
	friend class Api;
public:
	FriendRequest();
	FriendRequest(User*,User*);
	int get_id();
	User* get_from();
	User* get_to();
private:
	void set_id();
	int id;
	User* from;
	User* to;
	static int count;
};
#endif
