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
	int n = read(client_fd, buf, BUF_SIZE);//sizeof(buf));
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
		for(Value::ConstMemberIterator m = itr->MemberBegin(); m != itr->MemberEnd(); ++m)
			params[m->name.GetString()] = m->value.GetString();
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
	try {
		core->login(params["username"],params["password"]);
		send_suc();
	} catch (Exception e) {
		send_exp(e);
	}
}

void ConnectionHandler::call_logout()
{
	try {
		core->logout();
		send_suc();
	} catch (Exception e) {
		send_exp(e);
	}
}

void ConnectionHandler::call_signup()
{
	try {
		core->sign_up(params["username"], params["password"], params["name"], params["avatar_path"]);
		send_suc();
	} catch (Exception e) {
		send_exp(e);
	}
}

void ConnectionHandler::call_register()
{
	try {
		core->register_user(params["username"], params["password"], params["name"], params["avatar_path"]);
		send_suc();
	} catch (Exception e) {
		send_exp(e);
	}
}

void ConnectionHandler::call_get_avatar_path()
{
	try {
		string result = core->get_avatar_path();
		send_data(result);
	} catch (Exception e) {
		send_exp(e);
	}
}

void ConnectionHandler::call_get_username()
{
	try {
		string result = core->get_username();
		send_data(result);
	} catch (Exception e) {
		send_exp(e);
	}
}

void ConnectionHandler::call_get_latest_posts()
{
	try {
		vector <int> result = core->get_latest_posts();
		send_data(encode(result));
	} catch (Exception e) {
		send_exp(e);
	}
}

void ConnectionHandler::call_show_timelog()
{
	try {
		vector<int> result = core->show_timelog();
		send_data(encode(result));
	} catch (Exception e) {
		send_exp(e);
	}
}

void ConnectionHandler::call_post_photo()
{
	try {
		bool pub = false;
		if(params["publicity"] == "true")
			pub = true;
		core->post_photo(params["title"],params["CDN_path"], params["hashtags"], pub);
		send_suc();
	} catch (Exception e) {
		send_exp(e);
	}
}

void ConnectionHandler::call_get_my_latest_posts()
{
	try {
		vector<int> result = core->get_my_latest_posts();
		send_data(encode(result));
	} catch ( Exception e) {
		send_exp(e);
	}
}

void ConnectionHandler::call_get_friend_latest_posts()
{
	try {
		vector<int> result = core->get_friend_latest_posts(params["username"]);
		send_data(encode(result));
	} catch ( Exception e) {
		send_exp(e);
	}
}

void ConnectionHandler::call_get_user_public_posts()
{
	try {
		vector<int> result = core->get_user_public_posts(params["username"]);
		send_data(encode(result));
	} catch ( Exception e) {
		send_exp(e);
	}
}

void ConnectionHandler::call_get_my_latest_liked_posts()
{
	try {
		vector<int> result = core->get_my_latest_liked_posts();
		send_data(encode(result));
	} catch (Exception e) {
		send_exp(e);
	}
}

void ConnectionHandler::call_get_friend_latest_liked_posts()
{
	try {
		vector<int> result = core->get_friend_latest_liked_posts(params["username"]);
		send_data(encode(result));
	} catch (Exception e) {
		send_exp(e);
	}
}

void ConnectionHandler::call_get_friend_friends()
{
	try {
		vector<string> result = core->get_friend_friends(params["username"]);
		send_data(encode(result));
	} catch (Exception e) {
		send_exp(e);
	}
}

void ConnectionHandler::call_get_post_info()
{
	try {
		int id = atoi(params["id"].c_str());
		map<string,string> result = core->get_post_info(id);
		send_data(encode(result));
	} catch (Exception e) {
		send_exp(e);
	}
}

void ConnectionHandler::call_get_post_comments()
{
	try {
		int id = atoi(params["id"].c_str());
		vector<int> result = core->get_post_comments(id);
		send_data(encode(result));
	} catch (Exception e) {
		send_exp(e);
	}
}

void ConnectionHandler::call_get_post_hashtags()
{
	try {
		int id = atoi(params["id"].c_str());
		vector<string> result = core->get_post_hashtags(id);
		send_data(encode(result));
	} catch (Exception e) {
		send_exp(e);
	}
}


/*



vector<string> Core::get_post_hashtags(int id)
{

}

vector<string> Core::get_post_liked_by(int id)
{

}

map<string,string> Core::get_comment(int post_id, int comment_id)
{

}

map<int,string> Core::get_sent_requests()
{

}

map<int,string> Core::get_received_requests()
{

}

vector<string> Core::get_friends()
{
}

void Core::request_to_friend(string username)
{
}

void Core::approve_friend_request(int id)
{
}

void Core::approve_friend_request(string username)
{
}

void Core::disapprove_friend_request(int id)
{
}

void Core::disapprove_friend_request(string username)
{
}

void Core::remove_friend(string username)
{
}

void Core::report(string username)
{
}

void Core::update_user(string username, string password, string full_name, string avatar_path)
{
}


void Core::delete_user(string username)
{
}

void Core::like(int id)
{
}

bool Core::is_likable(int id)
{
}

void Core::unlike(int id)
{

}

vector<string> Core::get_users()
{

}

string Core::get_user_avatar(string username)
{
}

bool Core::is_friend_with(string username)
{

}

void Core::add_comment(int post_id, string content)
{
}

void Core::remove_comment(int comment_id)
{
}

bool Core::has_requested_to(string username)
{
}

bool Core::has_requested_to_me(string username)
{
}

bool Core::am_i_admin()
{
}

void Core::remove_user(string username)
{
} */
