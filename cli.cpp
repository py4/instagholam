#include "cli.h"
#include "api.h"
#include <string>
#include <iostream>
#include "parser/XML.h"

using namespace std;

CLI::CLI()
{
	api = new Api;
}

void CLI::start()
{
	string command_name;
	while(true)
	{

		cout << "> ";
		getline(cin,command);
		try {
			set_params(params,command);
			if(params["command"] == "register")
			{
				string username = params["username"];
				string password = params["password"];
				string name = params["name"];
				string avatar_path = params["avatar_path"];
				api->sign_up(username,password,name,avatar_path);
				continue;
			}
			else if(params["command"] == "login")
			{
				api->login(params["username"],params["password"]);
				continue;
			}
			else if(params["command"] == "logout")
			{
				api->logout();
				continue;
			}
			else if(params["command"] == "post_photo")
			{
				string title = params["title"];
				string CDN_path = params["CDN_path"];
				string hashtags = params["hashtags"];
				string publicity = params["publicity"];

				api->post_photo(title,CDN_path,hashtags, publicity == "true" ? true : false);
			}
			else if(params["command"] == "show_my_profile")
				show_my_profile();			
			else if(params["command"] == "show_friend_profile")
				show_friend_profile(params["username"]);
			else if(params["command"] == "request_to_friend")
				api->request_to_friend(params["username"]);
			else if(params["command"] == "get_users")
				show_users();
			else if(params["command"] == "disapprove_friend_request")
				api->disapprove_friend_request(to_int(params["id"]));
			else if(params["command"] == "quit")
				break;
			else {
				cout << "undefined command" << endl;
			}
			
		} catch (Exception e) {
			cerr << e.message << endl;
			continue;
		}
	}
}

void CLI::show_post(int id)
{
	map<string,string> post_info = api->get_post_info(id);
	cout << "title:  " << post_info["title"] << endl;
	cout << "photo_path:  " << post_info["photo_path"] << endl;
	cout << "created_at:  " << post_info["created_at"] << endl;
	cout << "publicity:  " << post_info["publicity"] << endl;
	vector<int> comment_ids = api->get_post_comments(id);
	cout << ">> comments <<" << endl;
	for(int i = 0; i < comment_ids.size(); i++)
	{
		map<string,string> comment_info = api->get_comment(id, comment_ids[i]);
		cout << "by:  " << comment_info["username"] << endl;
		cout << "content:  " << comment_info["content"] << endl;
		cout << "created_at:  " << comment_info["created_at"] << endl;
	}
}

void CLI::show_my_profile()
{

	vector <int> posts = api->get_my_latest_posts();
	cout << ">>>> posts <<<< " << endl;
	for(int i = 0; i < posts.size(); i++)
		show_post(posts[i]);

	cout << ">>> favorited posts <<<" << endl;
	vector <int> liked_posts = api->get_my_latest_liked_posts();
	for(int i = 0; i < liked_posts.size(); i++)
		show_post(liked_posts[i]);

	cout << ">>> sent requests <<<" << endl;
	map<int,string> sent_requests = api->get_sent_requests();
	for(map<int,string>::iterator it = sent_requests.begin(); it != sent_requests.end(); it++)
	{
		cout << "id:  " << it->first << endl;
		cout << "to:  " << it->second << endl;
	}

	cout << ">>> recieved requests <<<" << endl;
	map<int,string> recieved_requests = api->get_received_requests();
	for(map<int,string>::iterator it = recieved_requests.begin(); it != recieved_requests.end(); it++)
	{
		cout << "id:  " << it->first << endl;
		cout << "from:  " << it->second << endl;
	}

	cout << ">>> friends <<<" << endl;
	vector<string> friends = api->get_friends();
	for(int i = 0; i < friends.size(); i++)
		cout << "username:  " << friends[i] << endl;
}

void CLI::show_friend_profile(string username)
{
	vector<int> posts = api->get_friend_latest_posts(username);
	cout << "username:  " << username << endl;
	cout << ">>>> posts <<<" << endl;
	for(int i = 0; i < posts.size(); i++)
		show_post(posts[i]);

	cout << ">>>> favorited posts <<<< " << endl;
	vector<int> liked_posts = api->get_friend_latest_liked_posts(username);
	for(int i = 0; i < liked_posts.size(); i++)
		show_post(liked_posts[i]);

	cout << ">>> frinds <<<" << endl;
	vector<string> friends = api->get_friend_friends(username);
	for(int i = 0; i < friends.size(); i++)
		cout << "username:  " << friends[i] << endl;

	cout << ">>>> avatar <<<<" << endl;
	cout << "url:  " << api->get_user_avatar(username) << endl;
}

void CLI::show_users()
{
	cout << ">>>> users <<<<" << endl;
	vector<string> users = api->get_users();
	for(int i = 0; i < users.size(); i++)
		cout << users[i] << endl;
}