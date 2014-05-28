#include "cli.h"
#include "core.h"
#include <string>
#include <iostream>
#include "parser.h"
using namespace std;

CLI::CLI()
{
	//core = new Core;
}

CLI::~CLI()
{
	//DB::instance()->free_db();
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
				Core::instance()->instance()->sign_up(username,password,name,avatar_path);
				continue;
			}
			else if(params["command"] == "login")
			{
				Core::instance()->login(params["username"],params["password"]);
				continue;
			}
			else if(params["command"] == "logout")
			{
				Core::instance()->logout();
				continue;
			}
			else if(params["command"] == "post_photo")
			{
				string title = params["title"];
				string CDN_path = params["CDN_path"];
				string hashtags = params["hashtags"];
				string publicity = params["publicity"];

				Core::instance()->post_photo(title,CDN_path,hashtags, publicity == "true" ? true : false);
			}
			else if(params["command"] == "show_my_profile")
				show_my_profile();			
			else if(params["command"] == "get_post_info")
				show_post(to_int(params["id"]));
			else if(params["command"] == "is_likable")
				Core::instance()->is_likable(to_int(params["id"]));
			else if(params["command"] == "show_friend_profile")
				show_friend_profile(params["username"]);
			else if(params["command"] == "is_reportable")
				cout << Core::instance()->is_reportable(params["username"]) << endl;
			else if(params["command"] == "request_to_friend")
				Core::instance()->request_to_friend(params["username"]);
			else if(params["command"] == "get_users")
				show_users();
			else if(params["command"] == "disapprove_friend_request")
				Core::instance()->disapprove_friend_request(to_int(params["id"]));
			else if(params["command"] == "approve_friend_request")
				Core::instance()->approve_friend_request(to_int(params["id"]));
			else if(params["command"] == "remove_friend")
				Core::instance()->remove_friend(params["username"]);
			else if(params["command"] == "like_post")
				Core::instance()->like(to_int(params["id"]));
			else if(params["command"] == "unlike_post")
				Core::instance()->unlike(to_int(params["id"]));
			else if(params["command"] == "show_timelog")
				show_timelog();
			else if(params["command"] == "comment")
				Core::instance()->add_comment(to_int(params["id"]), params["content"]);
			else if(params["command"] == "remove_comment")
				Core::instance()->remove_comment(to_int(params["id"]));
			else if(params["command"] == "report")
				Core::instance()->report(params["username"]);
			else if(params["command"] == "update_user")
				Core::instance()->update_user(params["username"], params["password"], params["name"], params["avatar_path"]);
			else if(params["command"] == "delete_user")
				Core::instance()->delete_user(params["username"]);
			else if(params["command"] == "download")
				cout << Core::instance()->download_from_CDN(params["file_name"]);
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
	map<string,string> post_info = Core::instance()->get_post_info(id);
	cout << "username:  " << post_info["username"] << endl;
	cout << "title:  " << post_info["title"] << endl;
	cout << "photo_path:  " << post_info["photo_path"] << endl;
	cout << "created_at:  " << post_info["created_at"] << endl;
	cout << "publicity:  " << post_info["publicity"] << endl;
	vector<int> comment_ids = Core::instance()->get_post_comments(id);
	cout << "\t >> comments <<" << endl;
	for(int i = 0; i < comment_ids.size(); i++)
	{
		map<string,string> comment_info = Core::instance()->get_comment(id, comment_ids[i]);
		cout << "\t by:  " << comment_info["username"] << endl;
		cout << "\t content:  " << comment_info["content"] << endl;
		cout << "\t created_at:  " << comment_info["created_at"] << endl;
	}
	cout << "\t >> hashtags << " << endl;
	vector<string> hashtags = Core::instance()->get_post_hashtags(id);
	for(int i = 0; i < hashtags.size(); i++)
		cout << "\t " << hashtags[i] << endl;
	cout << "\t >> liked_by <<" << endl;
	vector<string> liked_by = Core::instance()->get_post_liked_by(id);
	for(int i = 0; i < liked_by.size(); i++)
		cout << "\t " << liked_by[i] << endl;
}

void CLI::show_my_profile()
{

	vector <int> posts = Core::instance()->get_my_latest_posts();
	cout << ">>>> posts <<<< " << endl;
	for(int i = 0; i < posts.size(); i++)
		show_post(posts[i]);

	cout << ">>> favorited posts <<<" << endl;
	vector <int> liked_posts = Core::instance()->get_my_latest_liked_posts();
	for(int i = 0; i < liked_posts.size(); i++)
		show_post(liked_posts[i]);

	cout << ">>> sent requests <<<" << endl;
	map<int,string> sent_requests = Core::instance()->get_sent_requests();
	for(map<int,string>::iterator it = sent_requests.begin(); it != sent_requests.end(); it++)
	{
		cout << "id:  " << it->first << endl;
		cout << "to:  " << it->second << endl;
	}

	cout << ">>> recieved requests <<<" << endl;
	map<int,string> recieved_requests = Core::instance()->get_received_requests();
	for(map<int,string>::iterator it = recieved_requests.begin(); it != recieved_requests.end(); it++)
	{
		cout << "id:  " << it->first << endl;
		cout << "from:  " << it->second << endl;
	}

	cout << ">>> friends <<<" << endl;
	vector<string> friends = Core::instance()->get_friends();
	for(int i = 0; i < friends.size(); i++)
		cout << "username:  " << friends[i] << endl;
}

void CLI::show_friend_profile(string username)
{
	vector<int> posts = Core::instance()->get_friend_latest_posts(username);
	cout << "username:  " << username << endl;
	cout << ">>>> posts <<<" << endl;
	for(int i = 0; i < posts.size(); i++)
		show_post(posts[i]);

	cout << ">>>> favorited posts <<<< " << endl;
	vector<int> liked_posts = Core::instance()->get_friend_latest_liked_posts(username);
	for(int i = 0; i < liked_posts.size(); i++)
		show_post(liked_posts[i]);

	cout << ">>> frinds <<<" << endl;
	vector<string> friends = Core::instance()->get_friend_friends(username);
	for(int i = 0; i < friends.size(); i++)
		cout << "username:  " << friends[i] << endl;

	cout << ">>>> avatar <<<<" << endl;
	cout << "url:  " << Core::instance()->get_user_avatar(username) << endl;
}

void CLI::show_users()
{
	cout << ">>>> users <<<<" << endl;
	vector<string> users = Core::instance()->get_users();
	for(int i = 0; i < users.size(); i++)
		cout << users[i] << endl;
}

void CLI::show_timelog()
{
	vector<int> posts = Core::instance()->get_latest_posts();
	for(int i = 0; i < posts.size(); i++)
		show_post(posts[i]);
}