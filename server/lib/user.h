#ifndef USER_H_
#define USER_H_
#include <vector>
#include <string>
#include "cvector.h"
#define latest_count 5

class Post;
class Comment;
class FriendRequest;
class Photo;
class UserReport;

class User
{
	friend class DB;
	friend class Core;
public:
	User();
	~User();
	User(std::string, std::string, std::string,std::string);
	bool is_admin();
	std::string get_username();
	std::string get_full_name();
	std::string get_avatar_path();

private:
	Post* post_photo(std::string,std::string,std::string, bool = false);
	cvector<int> get_latest_posts();
	cvector<int> get_latest_liked_posts();
	cvector<int> get_public_posts();
	cvector<Post*> get_latest_posts_full();
	cvector<std::string> get_friends();
	bool has_requested_to(User*);
	bool is_friend_with(User*);
	bool able_to_see(int);
	bool able_to_see(Post*);
	void request_to_friend(User*);
	void approve_friend_request(int);
	void disapprove_friend_request(int);
	void friend_request_approved(int);
	void friend_request_disapproved(int);
	void remove_friend(User*);
	bool reported_before(User*);	
	void report(std::string);
	void remove_comment_on_post(int);
	void remove_liked_post(int);
	void like(Post*);
	bool has_liked(Post*);
	Comment* get_comment(int);
		
	std::string username;
	std::string password;
	std::string full_name;
	Photo* avatar;
	cvector <Post*> posts;
	cvector <Post*> liked_posts;
	cvector <Comment*> comments;
	cvector <FriendRequest*> send_requests;
	cvector <FriendRequest*> received_requests;
	cvector <User*> friends;
	cvector <UserReport*> reports;
};
#endif
