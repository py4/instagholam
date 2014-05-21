#include "cli.h"
#include "api.h"
#include <string>
#include <iostream>
#include "parser/XML.h"

using namespace std;

CLI::CLI()
{
	//api = new Api;
}

CLI::~CLI()
{
	DB::instance()->free_db();
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
				Api::instance()->instance()->sign_up(username,password,name,avatar_path);
				continue;
			}
			else if(params["command"] == "login")
			{
				Api::instance()->login(params["username"],params["password"]);
				continue;
			}
			else if(params["command"] == "logout")
			{
				Api::instance()->logout();
				continue;
			}
			else if(params["command"] == "post_photo")
			{
				string title = params["title"];
				string CDN_path = params["CDN_path"];
				string hashtags = params["hashtags"];
				string publicity = params["publicity"];

				Api::instance()->post_photo(title,CDN_path,hashtags, publicity == "true" ? true : false);
			}
			else if(params["command"] == "show_my_profile")
				show_my_profile();			
			else if(params["command"] == "show_friend_profile")
				show_friend_profile(params["username"]);
			else if(params["command"] == "request_to_friend")
				Api::instance()->request_to_friend(params["username"]);
			else if(params["command"] == "get_users")
				show_users();
			else if(params["command"] == "disapprove_friend_request")
				Api::instance()->disapprove_friend_request(to_int(params["id"]));
			else if(params["command"] == "approve_friend_request")
				Api::instance()->approve_friend_request(to_int(params["id"]));
			else if(params["command"] == "remove_friend")
				Api::instance()->remove_friend(params["username"]);
			else if(params["command"] == "like_post")
				Api::instance()->like(to_int(params["id"]));
			else if(params["command"] == "unlike_post")
				Api::instance()->unlike(to_int(params["id"]));
			else if(params["command"] == "show_timelog")
				show_timelog();
			else if(params["command"] == "comment")
				Api::instance()->add_comment(to_int(params["id"]), params["content"]);
			else if(params["command"] == "remove_comment")
				Api::instance()->remove_comment(to_int(params["id"]));
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
	map<string,string> post_info = Api::instance()->get_post_info(id);
	cout << "username:  " << post_info["username"] << endl;
	cout << "title:  " << post_info["title"] << endl;
	cout << "photo_path:  " << post_info["photo_path"] << endl;
	cout << "created_at:  " << post_info["created_at"] << endl;
	cout << "publicity:  " << post_info["publicity"] << endl;
	vector<int> comment_ids = Api::instance()->get_post_comments(id);
	cout << "\t >> comments <<" << endl;
	for(int i = 0; i < comment_ids.size(); i++)
	{
		map<string,string> comment_info = Api::instance()->get_comment(id, comment_ids[i]);
		cout << "\t by:  " << comment_info["username"] << endl;
		cout << "\t content:  " << comment_info["content"] << endl;
		cout << "\t created_at:  " << comment_info["created_at"] << endl;
	}
	cout << "\t >> hashtags << " << endl;
	vector<string> hashtags = Api::instance()->get_post_hashtags(id);
	for(int i = 0; i < hashtags.size(); i++)
		cout << "\t " << hashtags[i] << endl;
	cout << "\t >> liked_by <<" << endl;
	vector<string> liked_by = Api::instance()->get_post_liked_by(id);
	for(int i = 0; i < liked_by.size(); i++)
		cout << "\t " << liked_by[i] << endl;
}

void CLI::show_my_profile()
{

	vector <int> posts = Api::instance()->get_my_latest_posts();
	cout << ">>>> posts <<<< " << endl;
	for(int i = 0; i < posts.size(); i++)
		show_post(posts[i]);

	cout << ">>> favorited posts <<<" << endl;
	vector <int> liked_posts = Api::instance()->get_my_latest_liked_posts();
	for(int i = 0; i < liked_posts.size(); i++)
		show_post(liked_posts[i]);

	cout << ">>> sent requests <<<" << endl;
	map<int,string> sent_requests = Api::instance()->get_sent_requests();
	for(map<int,string>::iterator it = sent_requests.begin(); it != sent_requests.end(); it++)
	{
		cout << "id:  " << it->first << endl;
		cout << "to:  " << it->second << endl;
	}

	cout << ">>> recieved requests <<<" << endl;
	map<int,string> recieved_requests = Api::instance()->get_received_requests();
	for(map<int,string>::iterator it = recieved_requests.begin(); it != recieved_requests.end(); it++)
	{
		cout << "id:  " << it->first << endl;
		cout << "from:  " << it->second << endl;
	}

	cout << ">>> friends <<<" << endl;
	vector<string> friends = Api::instance()->get_friends();
	for(int i = 0; i < friends.size(); i++)
		cout << "username:  " << friends[i] << endl;
}

void CLI::show_friend_profile(string username)
{
	vector<int> posts = Api::instance()->get_friend_latest_posts(username);
	cout << "username:  " << username << endl;
	cout << ">>>> posts <<<" << endl;
	for(int i = 0; i < posts.size(); i++)
		show_post(posts[i]);

	cout << ">>>> favorited posts <<<< " << endl;
	vector<int> liked_posts = Api::instance()->get_friend_latest_liked_posts(username);
	for(int i = 0; i < liked_posts.size(); i++)
		show_post(liked_posts[i]);

	cout << ">>> frinds <<<" << endl;
	vector<string> friends = Api::instance()->get_friend_friends(username);
	for(int i = 0; i < friends.size(); i++)
		cout << "username:  " << friends[i] << endl;

	cout << ">>>> avatar <<<<" << endl;
	cout << "url:  " << Api::instance()->get_user_avatar(username) << endl;
}

void CLI::show_users()
{
	cout << ">>>> users <<<<" << endl;
	vector<string> users = Api::instance()->get_users();
	for(int i = 0; i < users.size(); i++)
		cout << users[i] << endl;
}

void CLI::show_timelog()
{
	vector<int> posts = Api::instance()->get_latest_posts();
	for(int i = 0; i < posts.size(); i++)
		show_post(posts[i]);
}