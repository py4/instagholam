#ifndef API_H_
#define API_H_
#include <string>
#include "exception.h"
#include "db.h"
#include <ctime>
#include <vector>
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
	void like(int);
	std::string get_avatar_path();
	std::string get_username();
	 private:
User* current_user;
static bool compare_time(time_t&, time_t&);
static bool compare_post_time(Post*,Post*);
};
#endif
