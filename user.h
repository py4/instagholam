#ifndef USER_H_
#define USER_H_
#include <vector>
#include <string>

#define latest_count 5

class Post;
class Comment;
class FriendRequest;
class Photo;


class User
{
	friend class DB;
	friend class Api;
public:
	User();
	~User();
	User(std::string, std::string, std::string);
	bool is_admin();
	
private:
	void post_photo(std::string,std::string,std::string);
	std::vector<Post*> get_latest_posts();
	std::vector<Post*> get_latest_liked_posts();
	std::vector<std::string> get_friends();
	void add_to_friend(User*);
	void remove_friend(std::string);
	void report(std::string);
		
	std::string username;
	std::string password;
	std::string full_name;
	Photo* avatar;
	std::vector <Post*> posts;
	std::vector <Post*> liked_posts;
	std::vector <Comment*> comments;
	std::vector <FriendRequest*> send_requests;
	std::vector <FriendRequest> recieved_requests;
	std::vector <User*> friends;
};
#endif
