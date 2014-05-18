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
		} catch (string error) {
			cerr << error << endl;
			continue;
		}

		try {			
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
			{
				vector <int> posts = api->get_my_latest_posts();
				cout << ">>>> posts <<<< " << endl;
				for(int i = 0; i < posts.size(); i++)
				{
					map<string,string> post_info = api->get_post_info(posts[i]);
					cout << "title:  " << post_info["title"] << endl;
					cout << "photo_path:  " << post_info["url"] << endl;
					cout << "created_at:  " << post_info["created_at"] << endl;
					vector<int> comment_ids = api->get_post_comments(posts[i]);
					//XML* xml = new XML;
					//xml->load(api->get_post(posts[i]));
					//cout << "title:  " << xml->get_child_node("title")->get_value() << endl;
					//cout << "url:  " << xml->get_child_node("url")->get_value() << endl;
					//cout << ">> comments <<" << endl;
					//Node* comments_node = xml->get_child_node("comments");
					//for(int j = 0; j < )
				}
				/*std::string username;
				std::string password;
				std::string full_name;
				Photo* avatar;
				std::vector <Post*> posts;
				std::vector <Post*> liked_posts;
				std::vector <Comment*> comments;
				std::vector <FriendRequest*> send_requests;
				std::vector <FriendRequest*> received_requests;
				std::vector <User*> friends; */
			}
			else if(params["command"] == "quit")
			{
				break;
			}
			else {
				cout << "undefined command" << endl;
			}
			
		} catch (Exception e) {
			cerr << e.message << endl;
			continue;
		}
	}
}