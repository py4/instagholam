#ifndef API_H_
#define API_H_
#include <string>
#include "exception.h"
#include "db.h"
#include <ctime>
#include <vector>
#include "parser/XML.h"
#include <map>

class User;
class UserReport;
class Api
{
public:
	Api();
	void login(std::string,std::string);
	void logout();
	void sign_up(std::string,std::string,std::string,std::string);
	std::vector <int> get_latest_posts();
	std::vector <int> get_friend_requests();

	void request_to_friend(std::string);
	void approve_friend_request(int);
	void disapprove_friend_request(int);
	void remove_friend(std::string);
	void report(std::string);
	void delete_user(std::string);
		
	void post_photo(std::string, std::string);
	void remove_user(std::string);
	void post_photo(std::string, std::string, std::string, bool = false);
	std::vector <int> get_my_latest_posts();
	std::vector <int> get_my_latest_liked_posts();
	std::vector <std::string> get_friends();
	std::vector <std::string> get_users();
	std::string get_user_avatar(std::string);
	void like(int);
	void unlike(int);
	std::string get_avatar_path();
	std::string get_username();
	std::string get_post(int id);
	bool is_friend_with(std::string);

	//GETTER
	std::map<std::string,std::string> get_post_info(int);
	std::vector<int> get_post_comments(int);
	std::vector<std::string> get_post_hashtags(int);
	std::vector<std::string> get_post_liked_by(int);
	map<string,string> get_comment(int, int);
	map<int,string> get_sent_requests();
	map<int,string> get_received_requests();
	std::vector<int> get_friend_latest_liked_posts(std::string);
	std::vector<int> get_friend_latest_posts(std::string);
	std::vector<string> get_friend_friends(std::string);

	 private:
User* current_user;
static bool compare_time(time_t&, time_t&);
static bool compare_post_time(Post*,Post*);
};
#endif
