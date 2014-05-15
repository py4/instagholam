#ifndef API_H_
#define API_H_
#include <string>
#include "exception.h"
#include "db.h"
#include <ctime>
#include <vector>
class User;
class Api
{
public:
	Api();
	void login(std::string,std::string);
	void logout();
	void sign_up(std::string,std::string,std::string);
	std::vector <int> get_latest_posts();
	std::vector <int> get_friend_requests();
	void approve_friend_request(int);
	void disapprove_friend_request(int);
	void post_photo(std::string, std::string);
	void remove_user(std::string);
	void post_photo(std::string, std::string, std::string);
	 private:
User* current_user;
static bool compare_time(time_t&, time_t&);
static bool compare_post_time(Post*,Post*);
};
#endif
