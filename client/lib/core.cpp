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

void Core::login(string username, string password)
{
	Json json;
	json.AddMember("function","login");
	
	rapidjson::Value params(rapidjson::kArrayType);

	rapidjson::Value _username(rapidjson::kObjectType);
	_username.AddMember("username", username.c_str(),json.root.GetAllocator());
	rapidjson::Value _password(rapidjson::kObjectType);
	_password.AddMember("password",password.c_str(), json.root.GetAllocator());

	params.PushBack(_username, json.root.GetAllocator());
	params.PushBack(_password, json.root.GetAllocator());

	json.root.AddMember("params", params, json.root.GetAllocator());
	send(json.dump());
	simple_receive();
}

void Core::logout()
{
	Json json;
	json.AddMember("function", "logout");
	send(json.dump());
	simple_receive();
}

void Core::sign_up(string username, string password, string name, string avatar_path)
{
	Json json;
	json.AddMember("function","sign_up");
	
	rapidjson::Value params(rapidjson::kArrayType);

	rapidjson::Value _username(rapidjson::kObjectType);
	_username.AddMember("username", username.c_str(),json.root.GetAllocator());
	rapidjson::Value _password(rapidjson::kObjectType);
	_password.AddMember("password",password.c_str(), json.root.GetAllocator());
	rapidjson::Value _name(rapidjson::kObjectType);
	_password.AddMember("name",name.c_str(), json.root.GetAllocator());
	rapidjson::Value _avatar_path(rapidjson::kObjectType);
	_password.AddMember("avatar_path",avatar_path.c_str(), json.root.GetAllocator());

	params.PushBack(_username, json.root.GetAllocator());
	params.PushBack(_password, json.root.GetAllocator());
	params.PushBack(_name, json.root.GetAllocator());
	params.PushBack(_avatar_path, json.root.GetAllocator());

	json.root.AddMember("params", params, json.root.GetAllocator());
	send(json.dump());
	simple_receive();
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

void Core::register_user(string username, string password, string name, string avatar_path)
{
	Json json;
	json.AddMember("function","register_user");
	
	rapidjson::Value params(rapidjson::kArrayType);

	rapidjson::Value _username(rapidjson::kObjectType);
	_username.AddMember("username", username.c_str(),json.root.GetAllocator());
	rapidjson::Value _password(rapidjson::kObjectType);
	_password.AddMember("password",password.c_str(), json.root.GetAllocator());
	rapidjson::Value _name(rapidjson::kObjectType);
	_password.AddMember("name",name.c_str(), json.root.GetAllocator());
	rapidjson::Value _avatar_path(rapidjson::kObjectType);
	_password.AddMember("avatar_path",avatar_path.c_str(), json.root.GetAllocator());

	params.PushBack(_username, json.root.GetAllocator());
	params.PushBack(_password, json.root.GetAllocator());
	params.PushBack(_name, json.root.GetAllocator());
	params.PushBack(_avatar_path, json.root.GetAllocator());

	json.root.AddMember("params", params, json.root.GetAllocator());
	
	send(json.dump());
	simple_receive();
}

string Core::get_avatar_path()
{
	Json json;
	json.AddMember("function","get_avatar_path");
	send(json.dump());
	return receive_data();
}

string Core::get_username()
{
	Json json;
	json.AddMember("function","get_username");
	send(json.dump());
	return receive_data();
}

vector<int> Core::get_latest_posts()
{
	Json json;
	json.AddMember("function","get_latest_posts");
	send(json.dump());
	string data = receive_data();
	vector<int> result = decode <vector<int> >(data);
	return result;
}

vector<int> Core::show_timelog()
{
	Json json;
	json.AddMember("function","show_timelog");
	send(json.dump());
	string data = receive_data();
	vector<int> result = decode< vector<int> >(data);
	return result;
}

void set_params(Json& json)
{

}

//TODO: copying files into cache
//TODO: check image existence/validity
void Core::post_photo(string title,string CDN_path, string hashtags, bool publicity)
{
	Json json;
	json.AddMember("function","post_photo");
	
	rapidjson::Value params(rapidjson::kArrayType);

	rapidjson::Value _title(rapidjson::kObjectType);
	_title.AddMember("title", title.c_str(),json.root.GetAllocator());
	rapidjson::Value _CDN_path(rapidjson::kObjectType);
	_CDN_path.AddMember("CDN_path",CDN_path.c_str(), json.root.GetAllocator());
	rapidjson::Value _hashtags(rapidjson::kObjectType);
	_hashtags.AddMember("hashtags",hashtags.c_str(), json.root.GetAllocator());
	rapidjson::Value _publicity(rapidjson::kObjectType);
	_publicity.AddMember("publicity",publicity ? "true" : "false", json.root.GetAllocator());

	params.PushBack(_title, json.root.GetAllocator());
	params.PushBack(_CDN_path, json.root.GetAllocator());
	params.PushBack(_hashtags, json.root.GetAllocator());
	params.PushBack(_publicity, json.root.GetAllocator());

	json.root.AddMember("params", params, json.root.GetAllocator());
	
	send(json.dump());
	simple_receive();
}

vector<int> Core::get_my_latest_posts()
{
	Json json;
	json.AddMember("function","get_my_latest_posts");
	send(json.dump());
	string data = receive_data();
	vector<int> result = decode< vector<int> >(data);
	return result;
}

vector<int> Core::get_friend_latest_posts(string username)
{
	Json json;
	json.AddMember("function","get_friend_latest_posts");
	map<string,string> params;
	params["username"] = username;
 	json.set_params(params);
 	send(json.dump());
 	string data = receive_data();
	vector<int> result = decode< vector<int> >(data);
	return result;
}

vector <int> Core::get_user_public_posts(string username)
{
	Json json;
	json.AddMember("function","get_user_public_posts");
	map<string,string> params;
	params["username"] = username;
	json.set_params(params);
	send(json.dump());
	string data = receive_data();
	vector<int> result = decode< vector<int> >(data);
	return result;
}

vector<int> Core::get_my_latest_liked_posts()
{
	Json json;
	json.AddMember("function","get_my_latest_liked_posts");
	send(json.dump());
	string data = receive_data();
	vector<int> result = decode< vector<int> >(data);
	return result;
}

vector<int> Core::get_friend_latest_liked_posts(string username)
{
	Json json;
	json.AddMember("function","get_friend_latest_liked_posts");
	map<string,string> params;
	params["username"] = username;
	json.set_params(params);
	send(json.dump());
	string data = receive_data();
	vector<int> result = decode< vector<int> >(data);
	return result;
}

vector<string> Core::get_friend_friends(string username)
{
	Json json;
	json.AddMember("function","get_friend_friends");
	map<string,string> params;
	params["username"] = username;
	json.set_params(params);
	send(json.dump());
	string data = receive_data();
	vector<string> result = decode<vector<string> >(data);
	return result;
}	

map<string,string> Core::get_post_info(int id)
{
	Json json;
	json.AddMember("function","get_post_info");
	map<string,string> params;
	params["id"] = to_string(id);
	json.set_params(params);

	send(json.dump());
	string data = receive_data();
	map<string, string> result = decode<map<string,string> >(data);
	return result;
}

vector<int> Core::get_post_comments(int id)
{
	Json json;
	json.AddMember("function","get_post_comments");
	map<string,string> params;
	params["id"] = to_string(id);
	json.set_params(params);

	send(json.dump());
	string data = receive_data();
	vector<int> result = decode< vector<int> > (data);
	return result;
}

vector<string> Core::get_post_hashtags(int id)
{
	Json json;
	json.AddMember("function", "get_post_hashtags");
	map<string,string> params;
	params["id"] = to_string(id);
	json.set_params(params);

	send(json.dump());
	stringr data = receive_data();

	vector<string> result = decode < vector<string> > (data);
	return result;
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
}
