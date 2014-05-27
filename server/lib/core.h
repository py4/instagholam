#ifndef API_H_
#define API_H_
#include <string>
#include "exception.h"
#include "db.h"
#include <ctime>
#include <vector>
#include <map>

class User;
class UserReport;
class Core
{
public:
	Core();
	~Core();
	//static Core* instance();
	void login(std::string,std::string);
	void logout();
	void sign_up(std::string,std::string,std::string,std::string);
	void register_user(std::string,std::string,std::string,std::string);
	std::vector <int> get_latest_posts();
	std::vector <int> get_friend_requests();

	void request_to_friend(std::string);
	void approve_friend_request(int);
	void approve_friend_request(std::string);
	void disapprove_friend_request(int);
	void disapprove_friend_request(std::string);
	void remove_friend(std::string);
	void report(std::string);

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
	bool is_likable(int);
	std::string get_avatar_path();
	std::string get_username();
	std::string get_post(int id);
	bool is_friend_with(std::string);
	bool has_requested_to(std::string);
	bool has_requested_to_me(std::string);
	bool am_i_admin();
	void add_comment(int,std::string);
	void remove_comment(int);
	void update_user(std::string, std::string, std::string, std::string);
	void remove_user_posts(User*);
	void remove_user_liked_by(User*);
	void remove_user_comments(User*);
	void remove_user_send_requests(User*);
	void remove_user_received_requests(User*);
	void remove_user_friends(User*);
	void remove_user_reports(User*);
	void delete_user(std::string);
	//GETTER
	std::map<std::string,std::string> get_post_info(int);
	std::vector<int> get_post_comments(int);
	std::vector<std::string> get_post_hashtags(int);
	std::vector<std::string> get_post_liked_by(int);
    std::map<std::string,std::string> get_comment(int, int);
    std::map<int,std::string> get_sent_requests();
    std::map<int,std::string> get_received_requests();
	std::vector<int> get_friend_latest_liked_posts(std::string);
	std::vector<int> get_friend_latest_posts(std::string);
	std::vector<int> get_user_public_posts(std::string);
	std::vector<std::string> get_friend_friends(std::string);
	std::vector<int> show_timelog();

private:
	User* current_user;
	static bool compare_time(time_t&, time_t&);
	static bool compare_post_time(Post*,Post*);

	//Core();
	//Core(Core const&);
	//~Core();
	//void operator=(Core const&);
	//static Core* core;
};
#endif
