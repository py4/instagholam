#include "core.h"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/map.hpp>
#include "json.h"
#include "exception.h"
#include <sstream>
#include "parser.h"
using namespace std;

template<typename Archive>
void serialize(Archive& ar, std::vector<int>& objs, const unsigned version) {
  ar & objs;
}

template<typename Archive>
void serialize(Archive& ar, std::vector<std::string>& objs, const unsigned version) {
  ar & objs;
}

template <typename T>
T decode(string encoded)
{
	stringstream ss(encoded);
	boost::archive::text_iarchive ar(ss);
	T b;
	ar & b;
	return b;
}

Core* Core::core = NULL;

Core::Core()
{
	try {
		ClientHandler::init();
	} catch (const char* e) {
		cerr << e << endl;
		return;
	}
}

Core* Core::instance()
{
	if(core == NULL)
	{
		core = new Core;
		return core;
	}
	return core;
}

void Core::send_req(string func, map<string,string>& params)
{
	Json json;
	json.AddMember("function",func.c_str());
	json.set_params(params);
	Core::instance()->send(json.dump());
}

void Core::send_req(string func)
{
	Json json;
	json.AddMember("function",func.c_str());
	Core::instance()->send(json.dump());
}

void Core::send(string request)
{
	try {
		cout << "sending:  " << request << endl;
		ClientHandler::send(request);
	} catch (const char* e) {
		cerr << e << endl;
		return;
	}
}

void Core::simple_receive()
{
	try {
		string response = ClientHandler::receive();
		rapidjson::Document root;
		root.Parse<0>(response.c_str());

		if(root["error"].GetType())
			throw Exception(root["error"].GetString());
		else
			cout << response << endl;

	} catch (const char* e) {
		cerr << e << endl;
		return;
	}
}

string Core::receive_data()
{
	try {
		string response = ClientHandler::receive();
		rapidjson::Document root;
		root.Parse<0>(response.c_str());

		if(root["error"].GetType())
			throw Exception(root["error"].GetString());
		else
			cout << response << endl;

		return root["data"].GetString();

	} catch (const char* e) {
		cerr << e << endl;
		return "";
	}
}


void Core::login(string username, string password)
{
	Json json;
	map<string,string> params;
	params["username"] = username;
	params["password"] = password;
	send_req("login",params);

	simple_receive();
}

void Core::logout()
{
	Json json;
	send_req("logout");

	simple_receive();
}

void Core::sign_up(string username, string password, string name, string avatar_path)
{
	Json json;
	map<string,string> params;
	params["username"] = username;
	params["password"] = password;
	params["name"] = name;
	params["avatar_path"] = avatar_path;
	send_req("sign_up",params);

	simple_receive();
}

void Core::register_user(string username, string password, string name, string avatar_path)
{
	Json json;
	map<string,string> params;
	params["username"] = username;
	params["password"] = password;
	params["name"] = name;
	params["avatar_path"] = avatar_path;
	send_req("register_user",params);

	simple_receive();
}

string Core::get_avatar_path()
{
	Json json;
	send_req("get_avatar_path");

	return receive_data();
}

string Core::get_username()
{
	Json json;
	send_req("get_username");
	
	return receive_data();
}

vector<int> Core::get_latest_posts()
{
	Json json;
	send_req("get_latest_posts");
	
	string data = receive_data();
	vector<int> result = decode <vector<int> >(data);
	return result;
}

vector<int> Core::show_timelog()
{
	Json json;
	send_req("show_timelog");
	
	string data = receive_data();
	vector<int> result = decode< vector<int> >(data);
	return result;
}

void Core::post_photo(string title,string CDN_path, string hashtags, bool publicity)
{
	Json json;
	map<string,string> params;
	params["title"] = title;
	params["CDN_path"] = CDN_path;
	params["hashtags"] = hashtags;
	params["publicity"] = publicity ? "true" : "false";
	send_req("post_photo", params);

	simple_receive();
}

vector<int> Core::get_my_latest_posts()
{
	Json json;
	send_req("get_my_latest_posts");

	string data = receive_data();
	vector<int> result = decode< vector<int> >(data);
	return result;
}

vector<int> Core::get_friend_latest_posts(string username)
{
	Json json;
	map<string,string> params;
	params["username"] = username;
 	send_req("get_friend_latest_posts",params);

 	string data = receive_data();
	vector<int> result = decode< vector<int> >(data);
	return result;
}

vector <int> Core::get_user_public_posts(string username)
{
	Json json;
	map<string,string> params;
	params["username"] = username;
	send_req("get_user_public_posts",params);

	string data = receive_data();
	vector<int> result = decode< vector<int> >(data);
	return result;
}

vector<int> Core::get_my_latest_liked_posts()
{
	Json json;
	send_req("get_my_latest_liked_posts");

	string data = receive_data();
	vector<int> result = decode< vector<int> >(data);
	return result;
}

vector<int> Core::get_friend_latest_liked_posts(string username)
{
	Json json;
	map<string,string> params;
	params["username"] = username;
	send_req("get_friend_latest_liked_posts",params);

	string data = receive_data();
	vector<int> result = decode< vector<int> >(data);
	return result;
}

vector<string> Core::get_friend_friends(string username)
{
	Json json;
	map<string,string> params;
	params["username"] = username;
	send_req("get_friend_friends",params);

	string data = receive_data();
	vector<string> result = decode<vector<string> >(data);
	return result;
}	

map<string,string> Core::get_post_info(int id)
{
	Json json;
	map<string,string> params;
	params["id"] = to_string(id);
	send_req("get_post_info",params);

	string data = receive_data();
	map<string, string> result = decode<map<string,string> >(data);
	return result;
}

vector<int> Core::get_post_comments(int id)
{
	Json json;
	map<string,string> params;
	params["id"] = to_string(id);
	send_req("get_post_comments",params);

	string data = receive_data();
	vector<int> result = decode< vector<int> > (data);
	return result;
}

vector<string> Core::get_post_hashtags(int id)
{
	Json json;
	map<string,string> params;
	params["id"] = to_string(id);
	send_req("get_post_hashtags",params);

	string data = receive_data();
	vector<string> result = decode < vector<string> > (data);
	return result;
}

vector<string> Core::get_post_liked_by(int id)
{
	Json json;
	map<string,string> params;
	params["id"] = to_string(id);
	send_req("get_post_liked_by",params);

	string data = receive_data();
	vector<string> result = decode < vector<string> > (data);
	return result;
}

map<string,string> Core::get_comment(int post_id, int comment_id)
{
	Json json;
	map<string,string> params;
	params["post_id"] = to_string(post_id);
	params["comment_id"] = to_string(comment_id);
	send_req("get_post_comments",params);

	string data = receive_data();
	map<string,string> result = decode < map<string,string> > (data);
	return result;
}

map<int,string> Core::get_sent_requests()
{
	Json json;
	send_req("get_sent_requests");

	string data = receive_data();
	map<int, string> result = decode < map<int, string> > (data);
	return result;
}

map<int,string> Core::get_received_requests()
{
	Json json;
	send_req("get_received_requests");
	
	string data = receive_data();
	map<int, string> result = decode < map<int, string> > (data);
	return result;
}

vector<string> Core::get_friends()
{
	Json json;
	send_req("get_friends");
	
	string data = receive_data();
	vector<string> result = decode < vector<string> > (data);
	return result;
}

void Core::request_to_friend(string username)
{
	Json json;
	map<string,string> params;
	params["username"] = username;
	send_req("request_to_friend",params);
	simple_receive();
}

void Core::approve_friend_request(int id)
{
	Json json;
	map<string,string> params;
	params["id"] = to_string(id);
	send_req("approve_friend_request_with_id",params);
	simple_receive();
}

void Core::approve_friend_request(string username)
{
	Json json;
	map<string,string> params;
	params["username"] = username;
	send_req("approve_friend_request_with_username",params);
	simple_receive();
}

void Core::disapprove_friend_request(int id)
{
	Json json;
	map<string,string> params;
	params["id"] = to_string(id);
	send_req("disapprove_friend_request_with_id",params);
	simple_receive();
}

void Core::disapprove_friend_request(string username)
{
	Json json;
	map<string,string> params;
	params["username"] = username;
	send_req("disapprove_friend_request_with_username", params);
	simple_receive();
}

void Core::remove_friend(string username)
{
	Json json;
	map<string,string> params;
	params["username"] = username;
	send_req("report",params);
	simple_receive();
}

void Core::report(string username)
{
	Json json;
	map<string,string> params;
	params["username"] = username;
	send_req("report",params);
	simple_receive();
}

void Core::update_user(string username, string password, string full_name, string avatar_path)
{
	Json json;
	map<string,string> params;
	params["username"] = username;
	params["password"] = password;
	params["full_name"] = full_name;
	params["avatar_path"] = avatar_path;
	send_req("update_user", params);
	simple_receive();
}


void Core::delete_user(string username)
{
	Json json;
	map<string,string> params;
	params["username"] = username;
	send_req("delete_user", params);
	simple_receive();
}

void Core::like(int id)
{
	map<string,string> params;
	params["id"] = to_string(id);
	send_req("like",params);
	simple_receive();
}

bool Core::is_likable(int id)
{
	map<string,string> params;
	params["id"] = to_string(id);
	send_req("is_likable",params);

	string data = receive_data();
	cout << "boolean data:  " << data << endl;
	if(data == "true")
		return true;
	else
		return false;
}

void Core::unlike(int id)
{
	map<string,string> params;
	params["id"] = to_string(id);
	send_req("unlike",params);
	simple_receive();
}

vector<string> Core::get_users()
{
	send_req("get_users");

	string data = receive_data();
	vector<string> result = decode < vector<string> > (data);

	return result;
}

string Core::get_user_avatar(string username)
{
	map<string,string> params;
	params["username"] = username;
	send_req("get_user_avatar",params);

	string data = receive_data();
	return data;
}

bool Core::is_friend_with(string username)
{
	map<string,string> params;
	params["username"] = username;
	send_req("is_friend_with",params);

	string result = receive_data();
	if(result == "true")
		return true;
	else
		return false;
}

void Core::add_comment(int post_id, string content)
{
	map<string,string> params;
	params["post_id"] = to_string(post_id);
	params["content"] = content;
	send_req("add_comment",params);
	simple_receive();
}

void Core::remove_comment(int comment_id)
{
	map<string,string> params;
	params["comment_id"] = to_string(comment_id);
	send_req("remove_comment",params);
	simple_receive();
}

bool Core::has_requested_to(string username)
{
	map<string,string> params;
	params["username"] = username;
	send_req("has_requested_to",params);

	string result = receive_data();
	if(result == "true")
		return true;
	else
		return false;
}

bool Core::has_requested_to_me(string username)
{
	map<string,string> params;
	params["username"] = username;
	send_req("has_requested_to_me", params);

	string result = receive_data();
	if(result == "true")
		return true;
	else
		return false;
}

bool Core::am_i_admin()
{
	send_req("am_i_admin");
	string result = receive_data();
	if(result == "true")
		return true;
	else
		return false;
}

void Core::remove_user(string username)
{
	map<string,string> params;
	params["username"] = username;
	send_req("remove_user", params);
	simple_receive();
}
