#include <iostream>
#include "connection_handler.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "core.h"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/serialization.hpp>
#include <sstream>
using namespace std;
using namespace rapidjson;

template<typename T>
std::string encode(T& t)
{
	stringstream ss;
	boost::archive::text_oarchive oa(ss);
	oa << t;
	return ss.str();
}

ConnectionHandler::ConnectionHandler(int fd)
{
	core = new Core;
	client_fd = fd;
}

void ConnectionHandler::run()
{
	while (true)
	{
		string result = receive();
		cout << "result:  " << result << endl;
		if(result == "quit")
			break;

		rapidjson::Document root;
		root.Parse<0>(result.c_str());
		set_params(root);

		string func = root["function"].GetString();
		try {
			if(func == "login")
				call_login();
			if(func == "sign_up")
				call_signup();
			if(func == "logout")
				call_logout();
			if(func == "register_user")
				call_register();
			if(func == "get_avatar_path")
				call_get_avatar_path();
			if(func == "get_username")
				call_get_username();
			if(func == "get_latest_posts")
				call_get_latest_posts();
			if(func == "show_timelog")
				call_show_timelog();
			if(func == "post_photo")
				call_post_photo();
			if(func == "get_my_latest_posts")
				call_get_my_latest_posts();
			if(func == "get_friend_latest_posts")
				call_get_friend_latest_posts();
			if(func == "get_user_public_posts")
				call_get_user_public_posts();
			if(func == "get_my_latest_liked_posts")
				call_get_my_latest_liked_posts();
			if(func == "get_friend_latest_liked_posts")
				call_get_friend_latest_liked_posts();
			if(func == "get_friend_friends")
				call_get_friend_friends();
			if(func == "get_post_info")
				call_get_post_info();
			if(func == "get_post_comments")
				call_get_post_comments();
			if(func == "get_post_hashtags")
				call_get_post_hashtags();
			if(func == "get_post_liked_by")
				call_get_post_liked_by();
			if(func == "get_comment")
				call_get_comment();
			if(func == "get_sent_requests")
				call_get_sent_requests();
			if(func == "get_received_requests")
				call_get_received_requests();
			if(func == "get_friends")
				call_get_friends();
			if(func == "request_to_friend")
				call_request_to_friend();
			if(func == "approve_friend_request_with_id")
				call_approve_friend_request_with_id();
			if(func == "approve_friend_request_with_username")
				call_approve_friend_request_with_username();
			if(func == "disapprove_friend_request_with_id")
				call_disapprove_friend_request_with_id();
			if(func == "disapprove_friend_request_with_username")
				call_disapprove_friend_request_with_username();
			if(func == "remove_friend")
				call_remove_friend();
			if(func == "report")
				call_report();
			if(func == "update_user")
				call_update_user();
			if(func == "delete_user")
				call_delete_user();
			if(func == "like")
				call_like();
			if(func == "is_likable")
				call_is_likable();
			if(func == "unlike")
				call_unlike();
			if(func == "get_users")
				call_get_users();
			if(func == "get_user_avatar")
				call_get_user_avatar();
			if(func == "is_friend_with")
				call_is_friend_with();
			if(func == "add_comment")
				call_add_comment();
			if(func == "remove_comment")
				call_remove_comment();
			if(func == "has_requested_to")
				call_has_requested_to();
			if(func == "has_requested_to_me")
				call_has_requested_to_me();

		} catch (Exception e) {
			send_exp(e);
		}
		//cout << "function:  " << root["Function"].GetString() << endl;
		//cout << "username:  " << root["username"].GetString() << endl;
		//cout << "password:  " << root["password"].GetString() << endl;
//		cout <<  buffer.GetString() << endl;

		if(result == "quit")
			break;
	}
	cerr << "closing " << client_fd << endl;
	close(client_fd);		
}

void ConnectionHandler::send(string content)
{
	char* buf = new char[content.size() + 1];
	memcpy(buf,content.c_str(), content.size());
	buf[content.size()] = 0;
	int n = write(client_fd, buf, strlen(buf));
	if(n < 0)
		throw "error in writing!\t";
	delete[] buf;
}

string ConnectionHandler::receive()
{
	char* buf = new char[BUF_SIZE];
	int n = read(client_fd, buf, BUF_SIZE);
	buf[n < BUF_SIZE - 1 ? n : BUF_SIZE - 1] = '\0';

	if(n < 0)
		throw "error in reading!\t";
	else
		return string(buf);
	delete[] buf;
}

void ConnectionHandler::set_params(rapidjson::Document& document)
{
	if(document["params"].GetType() == 0)
		return;
	for (Value::ConstValueIterator itr = document["params"].Begin(); itr != document["params"].End(); ++itr)
	{
		for(Value::ConstMemberIterator m = itr->MemberBegin(); m != itr->MemberEnd(); ++m)
			params[m->name.GetString()] = m->value.GetString();
	}
}

void ConnectionHandler::send_exp(Exception& e)
{
	Json json;
	json.AddMember("error", e.message.c_str());
	send(json.dump());
}

void ConnectionHandler::send_suc()
{
	Json json;
	json.AddMember("success","true");
	send(json.dump());
}

void ConnectionHandler::send_data(string data)
{
	Json json;
	json.AddMember("data",data.c_str());
	send(json.dump());
}

void ConnectionHandler::call_login()
{
	core->login(params["username"],params["password"]);
	send_suc();
}

void ConnectionHandler::call_logout()
{
	
	core->logout();
	send_suc();
}

void ConnectionHandler::call_signup()
{

	core->sign_up(params["username"], params["password"], params["name"], params["avatar_path"]);
	send_suc();
}

void ConnectionHandler::call_register()
{
	core->register_user(params["username"], params["password"], params["name"], params["avatar_path"]);
	send_suc();
}

void ConnectionHandler::call_get_avatar_path()
{
	
	string result = core->get_avatar_path();
	send_data(result);
}

void ConnectionHandler::call_get_username()
{
	string result = core->get_username();
	send_data(result);
}

void ConnectionHandler::call_get_latest_posts()
{

	vector <int> result = core->get_latest_posts();
	send_data(encode(result));
}

void ConnectionHandler::call_show_timelog()
{
	vector<int> result = core->show_timelog();
	send_data(encode(result));
}

void ConnectionHandler::call_post_photo()
{
	
	bool pub = false;
	if(params["publicity"] == "true")
		pub = true;
	core->post_photo(params["title"],params["CDN_path"], params["hashtags"], pub);
	send_suc();
}


void ConnectionHandler::call_get_my_latest_posts()
{
	vector<int> result = core->get_my_latest_posts();
	send_data(encode(result));
}

void ConnectionHandler::call_get_friend_latest_posts()
{
	vector<int> result = core->get_friend_latest_posts(params["username"]);
	send_data(encode(result));
}

void ConnectionHandler::call_get_user_public_posts()
{
	vector<int> result = core->get_user_public_posts(params["username"]);
	send_data(encode(result));
}

void ConnectionHandler::call_get_my_latest_liked_posts()
{
	vector<int> result = core->get_my_latest_liked_posts();
	send_data(encode(result));
}

void ConnectionHandler::call_get_friend_latest_liked_posts()
{
	vector<int> result = core->get_friend_latest_liked_posts(params["username"]);
	send_data(encode(result));
}

void ConnectionHandler::call_get_friend_friends()
{
	vector<string> result = core->get_friend_friends(params["username"]);
	send_data(encode(result));
}

void ConnectionHandler::call_get_post_info()
{
	int id = atoi(params["id"].c_str());
	map<string,string> result = core->get_post_info(id);
	send_data(encode(result));
}

void ConnectionHandler::call_get_post_comments()
{
	int id = atoi(params["id"].c_str());
	vector<int> result = core->get_post_comments(id);
	send_data(encode(result));
}

void ConnectionHandler::call_get_post_hashtags()
{
	int id = atoi(params["id"].c_str());
	vector<string> result = core->get_post_hashtags(id);
	send_data(encode(result));
}

void ConnectionHandler::call_get_post_liked_by()
{
	int id = atoi(params["id"].c_str());
	vector<string> result = core->get_post_liked_by(id);
	send_data(encode(result));
}

void ConnectionHandler::call_get_comment()
{
	int post_id = atoi(params["post_id"].c_str());
	int comment_id = atoi(params["comment_id"].c_str());
	map<string,string> result = core->get_comment(post_id, comment_id);
	send_data(encode(result));
}

void ConnectionHandler::call_get_sent_requests()
{
	map<int,string> result = core->get_sent_requests();
	send_data(encode(result));
}

void ConnectionHandler::call_get_received_requests()
{
	map<int, string> result = core->get_received_requests();
	send_data(encode(result));
}

void ConnectionHandler::call_get_friends()
{
	vector<string> result = core->get_friends();
	send_data(encode(result));
}

void ConnectionHandler::call_request_to_friend()
{
	core->request_to_friend(params["username"]);
	send_suc();
}

void ConnectionHandler::call_approve_friend_request_with_id()
{
	int id = atoi(params["id"].c_str());
	core->approve_friend_request(id);
	send_suc();
}

void ConnectionHandler::call_approve_friend_request_with_username()
{
	core->approve_friend_request(params["username"]);
	send_suc();
}

void ConnectionHandler::call_disapprove_friend_request_with_id()
{
	int id = atoi(params["id"].c_str());
	core->disapprove_friend_request(id);
	send_suc();
}

void ConnectionHandler::call_disapprove_friend_request_with_username()
{
	core->disapprove_friend_request(params["username"]);
	send_suc();
}

void ConnectionHandler::call_remove_friend()
{
	core->remove_friend(params["username"]);
	send_suc();
}

void ConnectionHandler::call_report()
{
	core->report(params["username"]);
	send_suc();
}

void ConnectionHandler::call_update_user()
{
	core->update_user(params["username"],params["password"],params["full_name"], params["avatar_path"]);
	send_suc();
}

void ConnectionHandler::call_delete_user()
{
	core->delete_user(params["username"]);
	send_suc();
}

void ConnectionHandler::call_like()
{
	core->like(atoi(params["id"].c_str()));
	send_suc();
}

void ConnectionHandler::call_is_likable()
{
	core->is_likable(atoi(params["id"].c_str()));
	send_suc();
}

void ConnectionHandler::call_unlike()
{
	core->unlike(atoi(params["id"].c_str()));
	send_suc();
}

void ConnectionHandler::call_get_users()
{
	vector<string> result = core->get_users();
	send_data(encode(result));	
}

void ConnectionHandler::call_get_user_avatar()
{
	string result = core->get_user_avatar(params["username"]);
	send_data(result);
}

void ConnectionHandler::call_is_friend_with()
{
	bool result = core->is_friend_with(params["username"]);
	send_data(result ? "true" : "false");
}

void ConnectionHandler::call_add_comment()
{
	int post_id = atoi(params["post_id"]);
	core->add_comment(post_id,params["content"]);
	send_suc();
}

void ConnectionHandler::call_remove_comment()
{
	int comment_id = atoi(params["comment_id"]);
	core->remove_comment(comment_id);
	send_suc();
}

void ConnectionHandler::call_has_requested_to()
{
	bool result = core->has_requested_to(params["username"])
	send_data(result ? "true" : "false");
}

void ConnectionHandler::call_has_requested_to_me()
{
	bool result = core->has_requested_to_me(params["username"]);
	send_data(result ? "true" : "false");
}
/*


bool Core::has_requested_to_me(string username)
{
}

bool Core::am_i_admin()
{
}

void Core::remove_user(string username)
{
} */
