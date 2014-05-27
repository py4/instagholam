#include "core.h"
#include "user.h"
#include <string>
#include <algorithm>
#include "post.h"
#include "friend_request.h"
#include "user_report.h"
#include <iostream>
#include "comment.h"
#include "hashtag.h"
#include "photo.h"

using namespace std;

//Core* Core::core = NULL;

Core::Core()
{
	current_user = NULL;
}

/*Core* Core::instance()
{
	if(core == NULL)
	{
		core = new Core;
		return core;
	}
	return core;
} */


void Core::login(string username, string password)
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

void Core::logout()
{
	if(current_user == NULL)
		throw NotLoggedIn();
	current_user = NULL;
	cout << "logged out successfully" << endl;
}

void Core::sign_up(string username, string password, string name, string avatar_path)
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

void Core::register_user(string username, string password, string name, string avatar_path)
{
	if(!current_user->is_admin())
		throw AccessDenied();
	if(username == "")
		throw EmptyUsername();
	if(password.length() < 5)
		throw BadPassword();	

	User* user = DB::instance()->get_user(username);
	if(user != NULL)
		throw UserExists();

	user = new User(username, password, name,avatar_path);
	DB::instance()->users.push_back(user);

	cout << "registered successfully" << endl;
}

string Core::get_avatar_path()
{
	return current_user->get_avatar_path();
}

string Core::get_username()
{
	return current_user->get_username();
}

vector<int> Core::get_latest_posts()
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

vector<int> Core::show_timelog()
{
	return get_latest_posts();
}

bool Core::compare_time(time_t& first, time_t& second)
{
	return difftime(first,second) > 0;
}

bool Core::compare_post_time(Post* post1, Post* post2)
{
	return compare_time(post1->created_at, post2->created_at);
}
//TODO: copying files into cache
//TODO: check image existence/validity
void Core::post_photo(string title,string CDN_path, string hashtags, bool publicity)
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
	cout << "publicity:  " << pub << endl;
	Post* post = current_user->post_photo(title,CDN_path,hashtags,pub);
	DB::instance()->posts.push_back(post);
	cout << "photo posted successfully" << endl;
}

vector<int> Core::get_my_latest_posts()
{
	if(current_user == NULL)
		throw NotLoggedIn();
	return current_user->get_latest_posts();
}

vector<int> Core::get_friend_latest_posts(string username)
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

vector <int> Core::get_user_public_posts(string username)
{
	User* user = DB::instance()->get_user(username);
	if(user == NULL)
		throw UserNotFound();
	return user->get_public_posts();
}

vector<int> Core::get_my_latest_liked_posts()
{
	if(current_user == NULL)
		throw NotLoggedIn();
	return current_user->get_latest_liked_posts();
}

vector<int> Core::get_friend_latest_liked_posts(string username)
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

vector<string> Core::get_friend_friends(string username)
{
	if(current_user == NULL)
		throw NotLoggedIn();
	User* user = DB::instance()->get_user(username);
	if(user == NULL)
		throw UserNotFound();
	//if(!current_user->is_friend_with(user))
	//	throw AccessDenied();
	return user->get_friends();	
}

// bool Core::get_publicity(int id)
// {
// 	Post* post = DB::instance()->get_post(id);
// 	if(!current_user->able_to_see(post))
// 		throw AccessDenied();
// 	return post->pub;
// }

// string Core::get_photo_url(int id)
// {
// 	Post* post = DB::instance()->get_post(id);
// 	if(!current_user->able_to_see(post))
// 		throw AccessDenied();
// 	return post->CDN_path;
// }

// string Core::get_photo_username(int id)
// {
// 	Post* post = DB::instance()->get_post(id);
// 	if(!current_user->able_to_see(post))
// 		throw AccessDenied();
// 	return post->user->username;
// }

// string Core::get_photo_title(int id)
// {
// 	Post* post = DB::instance()->get_post(id);
// 	if(!current_user->able_to_see(post))
// 		throw AccessDenied();
// 	return post->user->username;
// }
/*string Core::get_post(int id)
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
}*/

map<string,string> Core::get_post_info(int id)
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

vector<int> Core::get_post_comments(int id)
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

vector<string> Core::get_post_hashtags(int id)
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

vector<string> Core::get_post_liked_by(int id)
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

map<string,string> Core::get_comment(int post_id, int comment_id)
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

map<int,string> Core::get_sent_requests()
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

map<int,string> Core::get_received_requests()
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

vector<string> Core::get_friends()
{
	if(current_user == NULL)
		throw NotLoggedIn();
	return current_user->get_friends();
}

void Core::request_to_friend(string username)
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

void Core::approve_friend_request(int id)
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

void Core::approve_friend_request(string username)
{
	if(current_user == NULL)
		throw NotLoggedIn();
	for(int i = 0; i < current_user->received_requests.size(); i++)
	{
		if(current_user->received_requests[i]->from->username == username)
		{
			User* user = current_user->received_requests[i]->from;
			user->friend_request_approved(current_user->received_requests[i]->id);
			current_user->approve_friend_request(current_user->received_requests[i]->id);
			cout << "friend request successfully approved" << endl;
			return;
		}
	}
	throw FriendRequestNotFound();
}

void Core::disapprove_friend_request(int id)
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

void Core::disapprove_friend_request(string username)
{
	if(current_user == NULL)
		throw NotLoggedIn();
	for(int i = 0; i < current_user->received_requests.size(); i++)
	{
		if(current_user->received_requests[i]->from->username == username)
		{
			User* user = current_user->received_requests[i]->from;
			user->friend_request_disapproved(current_user->received_requests[i]->id);
			current_user->disapprove_friend_request(current_user->received_requests[i]->id);
			cout << "disapproved successfully" << endl;
			return;
		}
	}
	throw FriendRequestNotFound();
}

void Core::remove_friend(string username)
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

void Core::report(string username)
{
	if(current_user == NULL)
		throw NotLoggedIn();
	User* user = DB::instance()->get_user(username);
	if(user == NULL)
		throw UserNotFound();
	if(current_user->reported_before(user))
		throw ReportedBefore();
	if(user == current_user)
		throw CannotReportYourself();

	UserReport* report = new UserReport(current_user,user);
	DB::instance()->reports.push_back(report);
	current_user->reports.push_back(report);

	cout << "reported successfully" << endl;
}

void Core::update_user(string username, string password, string full_name, string avatar_path)
{
	if(current_user == NULL)
		throw AccessDenied();
	if(username == "")
		throw EmptyUsername();
	if(password.length() < 5)
		throw BadPassword();	

	User* user = DB::instance()->get_user(username);
	if(user != NULL and user != current_user)
		throw UserExists();

	current_user->username = username;
	current_user->password = password;
	current_user->full_name = full_name;

	if(current_user->avatar != NULL)
	{
		delete current_user->avatar;
		current_user->avatar = new Photo(avatar_path);
	}

	cout << "updated successfully" << endl;
}

void Core::remove_user_posts(User* user)
{
	for(vector<Post*>::iterator it = user->posts.begin(); it != user->posts.end(); it++)
	{
		for(vector<Comment*>::iterator jt = (*it)->comments.begin(); jt != (*it)->comments.end(); jt++)
		{
			(*jt)->user->comments.erase(std::remove((*jt)->user->comments.begin(), (*jt)->user->comments.end(), *jt), (*jt)->user->comments.end());
			delete *jt;
		}
		cout << "removed post comments" << endl;

		for(vector<User*>::iterator jt = (*it)->liked_by.begin(); jt != (*it)->liked_by.end(); jt++)
			(*jt)->liked_posts.erase(std::remove((*jt)->liked_posts.begin(), (*jt)->liked_posts.end(), *it), (*jt)->liked_posts.end());
		cout << "removed this post from users liked lists" << endl;

		delete *it;
	}
	user->posts.clear();	
}

void Core::remove_user_liked_by(User* user)
{
	for(vector<Post*>::iterator it = user->liked_posts.begin(); it != user->liked_posts.end(); it++)
		(*it)->liked_by.erase(std::remove((*it)->liked_by.begin(), (*it)->liked_by.end(), user), (*it)->liked_by.end());
	user->liked_posts.clear();

	cout << "removed user from liked_by of his favorite posts" << endl;
}

void Core::remove_user_comments(User* user)
{
	for(vector<Comment*>::iterator it = user->comments.begin(); it != user->comments.end(); it++)
	{
		(*it)->post->comments.erase(std::remove((*it)->post->comments.begin(), (*it)->post->comments.end(), *it), (*it)->post->comments.end());
		delete *it;
	}
	cout << "removed his comments on posts" << endl;
}

void Core::remove_user_send_requests(User* user)
{
	for(vector<FriendRequest*>::iterator it = user->send_requests.begin(); it != user->send_requests.end(); it++)
	{
		for(int i = 0; i < (*it)->to->received_requests.size(); i++)
		{
			if((*it)->to->received_requests[i]->from == user)
			{
				(*it)->to->received_requests.erase((*it)->to->received_requests.begin() + i);
				break;
			}
		}
		delete *it;
	}
	cout << "removed sent requests" << endl;
}

void Core::remove_user_received_requests(User* user)
{
	for(vector<FriendRequest*>::iterator it = user->received_requests.begin(); it != user->received_requests.end(); it++)
	{
		for(int i = 0; i < (*it)->from->send_requests.size(); i++)
		{
			if((*it)->from->send_requests[i]->to == user)
			{
				(*it)->from->send_requests.erase((*it)->from->send_requests.begin() + i);
				break;
			}
		}
		delete *it;
	}
	cout << "removed received requestts" << endl;	
}

void Core::remove_user_friends(User* user)
{
	for(vector<User*>::iterator it = user->friends.begin(); it != user->friends.end(); it++)
		(*it)->friends.erase(std::remove((*it)->friends.begin(), (*it)->friends.end(), user),(*it)->friends.end());
	user->friends.clear();

	cout << "cleated user's friend" << endl;
}

class Compare
{
public:
	Compare(User* user) : user(user) {}
	bool operator()(UserReport* report) {
		return report->get_from() == user;
	}
private:
	User* user;
};

void Core::remove_user_reports(User* user)
{
	DB::instance()->reports.erase(remove_if(DB::instance()->reports.begin(), DB::instance()->reports.end(), Compare(current_user)), DB::instance()->reports.end());
	for(int i = 0; i < user->reports.size(); i++)
		delete user->reports[i];
	user->reports.clear();

	cout << "cleared user reports" << endl;
}

void Core::delete_user(string username)
{
	if(current_user == NULL)
		throw NotLoggedIn();

	if(!current_user->is_admin())
		throw AccessDenied();
	
	User* user = DB::instance()->get_user(username);
	if(user == NULL)
		throw UserNotFound();
	if(user == current_user)
		throw AccessDenied();

	cout << "user avatar deleted" << endl;
	delete user->avatar;

	remove_user_posts(user);
	remove_user_liked_by(user);
	remove_user_comments(user);
	remove_user_send_requests(user);	
	remove_user_received_requests(user);
	remove_user_friends(user);
	remove_user_reports(user);

	DB::instance()->users.erase(remove(DB::instance()->users.begin(), DB::instance()->users.end(), user),
		DB::instance()->users.end());
	delete user;
}

void Core::like(int id)
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

bool Core::is_likable(int id)
{
	Post* post = DB::instance()->get_post(id);
	if(current_user == NULL)
		return false;
	if(post == NULL)
		return false;
	if(!current_user->able_to_see(post))
		return false;
	if(current_user->has_liked(post))
		return false;
	return true;
}

void Core::unlike(int id)
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

vector<string> Core::get_users()
{
	vector<string> result;
	for(int i = 0; i < DB::instance()->users.size(); i++)
		result.push_back(DB::instance()->users[i]->get_username());
	return result;
}

string Core::get_user_avatar(string username)
{
	User* user = DB::instance()->get_user(username);
	return user->get_avatar_path();
}

bool Core::is_friend_with(string username)
{
	User* user = DB::instance()->get_user(username);
	return current_user->is_friend_with(user);
}

void Core::add_comment(int post_id, string content)
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

void Core::remove_comment(int comment_id)
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

bool Core::has_requested_to(string username)
{
	if(current_user == NULL)
		throw NotLoggedIn();
	User* user = DB::instance()->get_user(username);
	if(user == NULL)
		throw UserNotFound();
	return current_user->has_requested_to(user);
}

bool Core::has_requested_to_me(string username)
{
	if(current_user == NULL)
		throw NotLoggedIn();
	User* user = DB::instance()->get_user(username);
	if(user == NULL)
		throw UserNotFound();
	return user->has_requested_to(current_user);
}

bool Core::am_i_admin()
{
	return current_user->is_admin();
}

void Core::remove_user(string username)
{
	if(current_user == NULL)
		throw NotLoggedIn();
	if(!current_user->is_admin())
		throw AccessDenied();
	User* user = DB::instance()->get_user(username);
	if(user == NULL)
		throw UserNotFound();
}

bool Core::is_reportable(string username)
{
	if(current_user == NULL)
		throw NotLoggedIn();
	User* user = DB::instance()->get_user(username);
	if(user == NULL)
		throw UserNotFound();
	if(current_user == user)
		return false;
	if(user->is_admin())
		return false;
	return true;
}
