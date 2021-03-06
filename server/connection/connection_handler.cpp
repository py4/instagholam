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
#include <Poco/Thread.h>
#include "server.h"

using namespace std;
using namespace rapidjson;
//using namespace Poco;

template<typename T>
std::string encode(T& t)
{
	stringstream ss;
	boost::archive::text_oarchive oa(ss);
	oa << t;
	return ss.str();
}

ConnectionHandler::ConnectionHandler(Server* server, int fd)
{
	core = new Core;
	client_fd = fd;
	this->server = server;
	try {
		init_file_server_com();
	} catch (string e) {
		cerr << e << endl;
		return;
	}
}

void ConnectionHandler::init_file_server_com()
{
	file_server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	int iSetOption = 1;
	setsockopt(file_server_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&iSetOption, sizeof(iSetOption));
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(FILE_SERVER_IP);
	serv_addr.sin_port = htons(FILE_SERVER_PORT);

	if(connect(file_server_fd, (struct sockaddr*)& serv_addr, sizeof(serv_addr)) == -1)
		throw string("Could not connect to the file server");
	else
		cout << "connected to file_server with fd " << file_server_fd << endl;
}


void ConnectionHandler::run()
{
	while (true)
	{
		cout << "[ConnectionHandler] waiting for new command" << endl;
		string result = receive();
		if(result == "")
		{
			cout << ">>>>> Closing " << client_fd << " because of empty query <<<<" << endl;
			close(client_fd);
			cout << ">>>> file_server with fd " << file_server_fd << " because of empty query <<<<" << endl; 
			close(file_server_fd);
			return;
		}
		cout << "Command received from " << client_fd << endl;
		if(result == "quit")
			break;

		rapidjson::Document root;
		root.Parse<0>(result.c_str());
		Poco::Mutex mutex;
		mutex.lock();
		cout << "before" << endl;
		get_params(params,root);
		cout << "after" << endl;
		mutex.unlock();
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
			if(func == "am_i_admin")
				call_am_i_admin();
			if(func == "remove_user")
				call_remove_user();
			if(func == "is_reportable")
				call_is_reportable();

		} catch (Exception e) {
			cerr << "here88888 exewf" << endl;
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
	server->send(client_fd, content);
}

string ConnectionHandler::receive()
{
	return server->receive(client_fd);

	/*char* buf = new char[BUF_SIZE];
	int n = read(client_fd, buf, BUF_SIZE);
	buf[n < BUF_SIZE - 1 ? n : BUF_SIZE - 1] = '\0';

	if(n < 0)
		throw "error in reading!\t";
	else
		return string(buf);
	delete[] buf; */
}

void ConnectionHandler::set_params(rapidjson::Document& document)
{
	params = get_params(document);
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

void ConnectionHandler::send_with_key(string data, string key)
{
	Json json;
	json.AddMember(key.c_str(), data.c_str());
	send(json.dump());
}

void ConnectionHandler::send_data(string data)
{
	send_with_key(data,"data");
	// Json json;
	// json.AddMember("data",data.c_str());
	// send(json.dump());
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
	cout << "[ConnectionHandler][call_post_photo] start" << endl;
	bool pub = false;
	if(params["publicity"] == "true")
		pub = true;
	//core->post_photo(params["title"],params["CDN_path"], params["hashtags"], pub);

	Json json;
	map<string,string> auth_params;
	auth_params["auth_token"] = AUTH_TOKEN;
	json.AddMember("function","generate_temp_token");
	json.set_params(auth_params);
	server->send(file_server_fd, json.dump());
	string user_token = server->receive(file_server_fd);
	cout << "result from temp token:  " << user_token << endl;

	send_with_key(user_token,"user_token");

	string CDN_path = receive();
	if(CDN_path == "quit")
	{
		cout << "quiting from call post photo" << endl;
		return;
	}
	cout << "Server received CDN_paht:  " << CDN_path << endl;
	core->post_photo(params["title"], CDN_path, params["hashtags"], pub);
	cout << "[ConnectionHandler] sending success to client" << endl;
	send_suc();
	cout << "[ConnectionHandler] success was sent to client" << endl;
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
	cout << "here!" << endl;
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
	bool result = core->is_likable(atoi(params["id"].c_str()));
	send_data(result ? "true" : "false");
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
	int post_id = atoi(params["post_id"].c_str());
	core->add_comment(post_id,params["content"]);
	send_suc();
}

void ConnectionHandler::call_remove_comment()
{
	int comment_id = atoi(params["comment_id"].c_str());
	core->remove_comment(comment_id);
	send_suc();
}

void ConnectionHandler::call_has_requested_to()
{
	bool result = core->has_requested_to(params["username"]);
	send_data(result ? "true" : "false");
}

void ConnectionHandler::call_has_requested_to_me()
{
	bool result = core->has_requested_to_me(params["username"]);
	send_data(result ? "true" : "false");
}

void ConnectionHandler::call_am_i_admin()
{
	bool result = core->am_i_admin();
	send_data(result ? "true" : "false");
}

void ConnectionHandler::call_remove_user()
{
	core->remove_user(params["username"]);
	send_suc();
}

void ConnectionHandler::call_is_reportable()
{
	bool result = core->is_reportable(params["username"]);
	send_data(result ? "true" : "false");
}
