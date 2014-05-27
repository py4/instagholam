#ifndef CONNECTION_HANDLER_
#define CONNECTION_HANDLER_

#include <cstring>
#include <Poco/Thread.h>
#include <map>
#include "json.h"
#include "exception.h"
#include "core.h"
#define BUF_SIZE 2000
class ConnectionHandler : public Poco::Runnable {
public:
	ConnectionHandler();
	ConnectionHandler(int);
	virtual void run();

private:
	void set_params(rapidjson::Document&);
	void send(std::string);
	std::string receive();
	int client_fd;
	std::map <std::string, std::string> params;

	void send_exp(Exception&);
	void send_suc();
	void send_data(std::string);
	void call_login();
	void call_logout();
	void call_signup();
	void call_register();
	void call_get_avatar_path();
	void call_get_username();
	void call_get_latest_posts();
	void call_show_timelog();
	void call_show_photo();
	void call_post_photo();
	void call_my_latest_posts();
	void call_get_friend_latest_posts();
	void call_get_user_public_posts();
	void call_get_my_latest_liked_posts();
	void call_get_my_latest_posts();
	void call_get_friend_latest_liked_posts();
	void call_get_friend_friends();		
	void call_get_post_info();
	void call_get_post_comments();
	void call_get_post_hashtags();
	void call_get_post_liked_by();
	void call_get_comment();
	void call_get_sent_requests();
	void call_get_received_requests();
	void call_get_friends();
	void call_request_to_friend();
	void call_approve_friend_request_with_id();
	void call_approve_friend_request_with_username();
	void call_disapprove_friend_request_with_id();
	void call_disapprove_friend_request_with_username();
	void call_remove_friend();
	void call_report();
	void call_update_user();
	void call_delete_user();
	void call_like();
	void call_is_likable();
	void call_unlike();
	void call_get_users();
	void call_get_user_avatar();
	void call_is_friend_with();
	void call_add_comment();
	void call_remove_comment();
	void call_has_requested_to();
	void call_has_requested_to_me();
	void call_am_i_admin();
	void call_remove_user();
	
	Core* core;
	};
#endif