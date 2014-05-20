#include "api.h"
#include "user.h"
#include <string>
#include <algorithm>
#include "post.h"
#include "friend_request.h"
#include "user_report.h"
#include <iostream>
#include "comment.h"
#include "hashtag.h"

using namespace std;

Api::Api()
{
	current_user = NULL;
}

void Api::login(string username, string password)
{
	if(current_user != NULL)
		throw AlreadyLoggedIn();
	User* user = DB::instance()->get_user(username);
	if(user == NULL)
		throw UserNotFound();
	if(user->password != password)
		throw WrongCredentials();
	current_user = user;
	cout << "logged in successfully" << endl;
}

void Api::logout()
{
	if(current_user == NULL)
		throw NotLoggedIn();
	current_user = NULL;
	cout << "logged out successfully" << endl;
}

void Api::sign_up(string username, string password, string name, string avatar_path)
{
	if(current_user != NULL)
		throw AlreadyLoggedIn();
	if(username == "")
		throw EmptyUsername();
	if(password.length() < 5)
		throw BadPassword();

	User* user = DB::instance()->get_user(username);
	if(user != NULL)
		throw UserExists();

	user = new User(username, password, name,avatar_path);
	DB::instance()->users.push_back(user);
	current_user = user;
	cout << "signed up successfully" << endl;
}

string Api::get_avatar_path()
{
	return current_user->get_avatar_path();
}

string Api::get_username()
{
	return current_user->get_username();
}

vector<int> Api::get_latest_posts()
{
	if(current_user == NULL)
		throw NotLoggedIn();
	vector<int> result;
	vector <Post*> all = current_user->get_latest_posts_full();
	for(int i = 0; i < current_user->friends.size(); i++)
	{
		vector <int> posts = current_user->friends[i]->get_latest_posts();
		for(int j = 0; j < posts.size(); j++)
		{
			Post* post = DB::instance()->get_post(posts[j]);
			if(post == NULL)
				cerr << "bug!" << endl;
			all.push_back(post);
		}
	}
	sort(all.begin(), all.end(), compare_post_time);
	for(int i = 0; i < 5; i++)
	{
		if(i >= all.size())
			break;
		if(all.size() - 1 - i >= 0)
			result.push_back(all[all.size() - 1 - i]->id);
		else
			break;
	}
	return result;
}

vector<int> Api::show_timelog()
{
	return get_latest_posts();
}

bool Api::compare_time(time_t& first, time_t& second)
{
	return difftime(first,second) > 0;
}

bool Api::compare_post_time(Post* post1, Post* post2)
{
	return compare_time(post1->created_at, post2->created_at);
}
//TODO: copying files into cache
//TODO: check image existence/validity
void Api::post_photo(string title,string CDN_path, string hashtags, bool publicity)
{
	if(current_user == NULL)
		throw NotLoggedIn();
	if(title == "")
		throw EmptyTitle();
	if(CDN_path == "")
		throw EmptyPhoto();

	bool pub = publicity;
	if(current_user->is_admin())
		pub = true;
	
	Post* post = current_user->post_photo(title,CDN_path,hashtags,pub);
	DB::instance()->posts.push_back(post);
	cout << "photo posted successfully" << endl;
}

vector<int> Api::get_my_latest_posts()
{
	if(current_user == NULL)
		throw NotLoggedIn();
	return current_user->get_latest_posts();
}

vector<int> Api::get_friend_latest_posts(string username)
{
	if(current_user == NULL)
		throw NotLoggedIn();
	User* user = DB::instance()->get_user(username);
	if(user == NULL)
		throw UserNotFound();
	if(!current_user->is_friend_with(user))
		throw AccessDenied();
	return user->get_latest_posts();
}

vector<int> Api::get_my_latest_liked_posts()
{
	if(current_user == NULL)
		throw NotLoggedIn();
	return current_user->get_latest_liked_posts();
}

vector<int> Api::get_friend_latest_liked_posts(string username)
{
	if(current_user == NULL)
		throw NotLoggedIn();
	User* user = DB::instance()->get_user(username);
	if(user == NULL)
		throw UserNotFound();
	if(!current_user->is_friend_with(user))
		throw AccessDenied();
	return user->get_latest_liked_posts();
}

vector<string> Api::get_friend_friends(string username)
{
	if(current_user == NULL)
		throw NotLoggedIn();
	User* user = DB::instance()->get_user(username);
	if(user == NULL)
		throw UserNotFound();
	if(!current_user->is_friend_with(user))
		throw AccessDenied();
	return user->get_friends();	
}

// bool Api::get_publicity(int id)
// {
// 	Post* post = DB::instance()->get_post(id);
// 	if(!current_user->able_to_see(post))
// 		throw AccessDenied();
// 	return post->pub;
// }

// string Api::get_photo_url(int id)
// {
// 	Post* post = DB::instance()->get_post(id);
// 	if(!current_user->able_to_see(post))
// 		throw AccessDenied();
// 	return post->CDN_path;
// }

// string Api::get_photo_username(int id)
// {
// 	Post* post = DB::instance()->get_post(id);
// 	if(!current_user->able_to_see(post))
// 		throw AccessDenied();
// 	return post->user->username;
// }

// string Api::get_photo_title(int id)
// {
// 	Post* post = DB::instance()->get_post(id);
// 	if(!current_user->able_to_see(post))
// 		throw AccessDenied();
// 	return post->user->username;
// }
string Api::get_post(int id)
{
	Post* post = DB::instance()->get_post(id);
 	if(!current_user->able_to_see(post))
 		throw AccessDenied();
	XML* xml = new XML;
	Node* publicity = xml->current_node->add_node("publicity");
	if(post->pub == true)
		publicity->set_value("true");
	else
		publicity->set_value("false");

	xml->current_node->add_node("username",post->user->username);
	xml->current_node->add_node("title",post->title);
	Node* comments = xml->current_node->add_node("comments");
	for(int i = 0; i < post->comments.size(); i++)
	{
		Node* comment = comments->add_node("comment");
		comment->add_node("user",post->comments[i]->get_user());
		comments->add_node("content", post->comments[i]->get_content());
	}
	Node* hashtags = xml->current_node->add_node("hashtags");
	for(int i = 0; i < post->hashtags.size(); i++)
		hashtags->add_node("hashtag",post->hashtags[i]->get_content());
	Node* liked_by = xml->current_node->add_node("liked_by");
	for(int i = 0; i < post->liked_by.size(); i++)
		liked_by->add_node("user",post->liked_by[i]->get_username());
	xml->current_node->add_node("created_at", post->get_created_at());
	xml->current_node->add_node("photo_path",post->get_path());
	return xml->dump();
}

map<string,string> Api::get_post_info(int id)
{
	Post* post = DB::instance()->get_post(id);
	if(post == NULL)
		throw PostNotFound();
	if(!current_user->able_to_see(post))
		throw AccessDenied();
	map<string,string> result;
	if(post->pub == true)
		result["publicity"] = "true";
	else
		result["publicity"] = "false";
	result["username"] = post->user->username;
	result["title"] = post->title;
	result["created_at"] = post->get_created_at();
	result["photo_path"] = post->get_path();
	return result;
}

vector<int> Api::get_post_comments(int id)
{
	Post* post = DB::instance()->get_post(id);
	if(post == NULL)
		throw PostNotFound();
	if(!current_user->able_to_see(post))
		throw AccessDenied();
	vector<int> result;
	for(int i = 0; i < post->comments.size(); i++)
		result.push_back(post->comments[i]->id);
	return result;
}

vector<string> Api::get_post_hashtags(int id)
{
	if(current_user == NULL)
		throw NotLoggedIn();
	Post* post = DB::instance()->get_post(id);
	if(post == NULL)
		throw PostNotFound();
	if(!current_user->able_to_see(post))
		throw AccessDenied();
	vector<string> result;
	for(int i = 0; i < post->hashtags.size(); i++)
		result.push_back(post->hashtags[i]->get_content());
	return result;
}

vector<string> Api::get_post_liked_by(int id)
{
	if(current_user == NULL)
		throw NotLoggedIn();
	Post* post = DB::instance()->get_post(id);
	if(post == NULL)
		throw PostNotFound();
	if(!current_user->able_to_see(post))
		throw AccessDenied();
	vector<string> result;
	for(int i = 0; i < post->liked_by.size(); i++)
		result.push_back(post->liked_by[i]->username);
	return result;
}

map<string,string> Api::get_comment(int post_id, int comment_id)
{
	Post* post = DB::instance()->get_post(post_id);
	if(post == NULL)
		throw PostNotFound();
	if(!current_user->able_to_see(post))
		throw AccessDenied();
	Comment* comment = post->get_comment(comment_id);
	if(comment == NULL)
		throw CommentNotFound();
	map<string,string> result;

	result["username"] = comment->user->username;
	result["created_at"] = comment->get_created_at();
	result["content"] = comment->content;
	return result;
}

map<int,string> Api::get_sent_requests()
{
	if(current_user == NULL)
		throw NotLoggedIn();
	map<int,string> result;
	for(int i = 0; i < current_user->send_requests.size(); i++)
	{
		int id = current_user->send_requests[i]->id;
		string from = current_user->send_requests[i]->to->username;
		result[id] = from;
	}
	return result;
}

map<int,string> Api::get_received_requests()
{
	if(current_user == NULL)
		throw NotLoggedIn();
	map<int,string> result;
	for(int i = 0; i < current_user->received_requests.size(); i++)
	{
		int id = current_user->received_requests[i]->id;
		string to = current_user->received_requests[i]->from->username;
		result[id] = to;
	}
	return result;
}

vector<string> Api::get_friends()
{
	if(current_user == NULL)
		throw NotLoggedIn();
	return current_user->get_friends();
}

void Api::request_to_friend(string username)
{
	if(current_user == NULL)
		throw NotLoggedIn();
	User* user = DB::instance()->get_user(username);
	if(user == current_user)
		throw FriendWithYourself();
	if(user == NULL)
		throw UserNotFound();
	if(current_user->has_requested_to(user))
		throw AlreadyRequested();
	if(user->has_requested_to(current_user))
		throw HeRequested();
	if(current_user->is_friend_with(user))
		throw AlreadyFriends();

	FriendRequest* request = new FriendRequest(current_user,user);
	current_user->send_requests.push_back(request);
	user->received_requests.push_back(request);
	cout << "Successfully requested to him/her" << endl;
}

void Api::approve_friend_request(int id)
{
	if(current_user == NULL)
		throw NotLoggedIn();
	for(int i = 0; i < current_user->received_requests.size(); i++)
		if(current_user->received_requests[i]->id == id)
		{
			User* user = current_user->received_requests[i]->from;
			user->friend_request_approved(id);
			current_user->approve_friend_request(id);
			cout << "friend request successfully approved" << endl;
			return;
		}
	throw FriendRequestNotFound();
}

void Api::disapprove_friend_request(int id)
{
	if(current_user == NULL)
		throw NotLoggedIn();
	for(int i = 0; i < current_user->received_requests.size(); i++)
	{
		if(current_user->received_requests[i]->id == id)
		{
			User* user = current_user->received_requests[i]->from;
			user->friend_request_disapproved(id);
			current_user->disapprove_friend_request(id);
			cout << "disapproved successfully" << endl;
			return;
		}
	}
	throw FriendRequestNotFound();
}

void Api::remove_friend(string username)
{
	User* user = DB::instance()->get_user(username);
	if(user == NULL)
		throw UserNotFound();
	if(!current_user->is_friend_with(user))
		throw NotFriends();

	user->remove_friend(current_user);
	current_user->remove_friend(user);

	cout << "removed successfully" << endl;
}

void Api::report(string username)
{
	User* user = DB::instance()->get_user(username);
	if(user == NULL)
		throw UserNotFound();
	if(current_user->is_friend_with(user))
		throw AlreadyFriends();
	if(current_user->reported_before(user))
		throw ReportedBefore();

	UserReport* report = new UserReport(current_user,user);
	DB::instance()->reports.push_back(report);
	current_user->reports.push_back(report);
}

void Api::delete_user(string username)
{
	if(!current_user->is_admin())
		throw AccessDenied();
	
	User* user = DB::instance()->get_user(username);
	if(user == NULL)
		throw UserNotFound();
	if(user == current_user)
		throw AccessDenied();
}

void Api::like(int id)
{
	Post* post = DB::instance()->get_post(id);
	if(current_user == NULL)
		throw NotLoggedIn();
	if(post == NULL)
		throw PostNotFound();
	if(!current_user->able_to_see(post))
		throw AccessDenied();
	if(current_user->has_liked(post))
		throw LikedBefore();
	
	current_user->liked_posts.push_back(post);
	post->liked_by.push_back(current_user);

	cout << "success fully liked" << endl;
}

void Api::unlike(int id)
{
	if(current_user == NULL)
		throw NotLoggedIn();
	Post* post = DB::instance()->get_post(id);
	if(post == NULL)
		throw PostNotFound();
	if(!current_user->able_to_see(post))
		throw AccessDenied();
	if(!current_user->has_liked(post))
		throw NotLikedBefore();

	vector <Post*>& posts = current_user->liked_posts;
	posts.erase(std::remove(posts.begin(), posts.end(), post), posts.end());
	vector <User*>& by = post->liked_by;
	by.erase(std::remove(by.begin(), by.end(), current_user), by.end());

	cout << "unliked successfully" << endl;
}

vector<string> Api::get_users()
{
	vector<string> result;
	for(int i = 0; i < DB::instance()->users.size(); i++)
		result.push_back(DB::instance()->users[i]->get_username());
	return result;
}

string Api::get_user_avatar(string username)
{
	User* user = DB::instance()->get_user(username);
	return user->get_avatar_path();
}

bool Api::is_friend_with(string username)
{
	User* user = DB::instance()->get_user(username);
	return current_user->is_friend_with(user);
}

void Api::add_comment(int post_id, string content)
{
	if(current_user == NULL)
		throw NotLoggedIn();
	Post* post = DB::instance()->get_post(post_id);
	if(post == NULL)
		throw PostNotFound();
	if(!current_user->able_to_see(post))
		throw AccessDenied();

	Comment* comment = new Comment(current_user, post, content);
	current_user->comments.push_back(comment);
	post->comments.push_back(comment);

	cout << "successfully submited" << endl;
}

void Api::remove_comment(int comment_id)
{
	if(current_user == NULL)
		throw NotLoggedIn();
	Comment* comment = current_user->get_comment(comment_id);
	if(comment == NULL)
		throw CommentNotFound();
	Post* post = comment->post;
	vector <Comment*>& comments = current_user->comments;
	comments.erase(std::remove(comments.begin(), comments.end(), comment), comments.end());
	vector <Comment*>& p_comments = post->comments;
	p_comments.erase(std::remove(p_comments.begin(), p_comments.end(), comment), p_comments.end());
	delete comment;
	cout << "removed successfully" << endl;
}














