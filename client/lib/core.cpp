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
		cout << "Client is connecting to file server..." << endl;
		file_server_fd = connect_to_file_server();
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

void Core::send_req(string func, map<string,string>& params, int fd)
{
	Json json;
	json.AddMember("function",func.c_str());
	json.set_params(params);
	Core::instance()->send(json.dump(), fd);
}

void Core::send_req(string func, int fd)
{
	Json json;
	json.AddMember("function",func.c_str());
	Core::instance()->send(json.dump(), fd);
}

void Core::send(string request, int fd)
{
	try {
		cout << "sending to " << fd << ":  " << request << endl;
		ClientHandler::send(request, fd);
	} catch (const char* e) {
		cerr << e << endl;
		return;
	}
}

void Core::simple_receive(int fd)
{
	try {
		string response = ClientHandler::receive(fd);
		rapidjson::Document root;
		root.Parse<0>(response.c_str());

		if(root["error"].GetType())
			throw Exception(root["error"].GetString());
		else if(root["success"].GetType())
			cout << response << endl;

	} catch (const char* e) {
		cerr << e << endl;
		return;
	}
}

string Core::receive_data(int fd)
{
	try {
		string response = ClientHandler::receive(fd);
		rapidjson::Document root;
		root.Parse<0>(response.c_str());

		if(root["error"].GetType())
			throw Exception(root["error"].GetString());
		else if(root["success"].GetType())
			cout << response << endl;

		return root["data"].GetString();

	} catch (const char* e) {
		cerr << e << endl;
		return "";
	}
}

string Core::simple_receive_data(int fd)
{
	try {
		string response = ClientHandler::receive(fd);
		return response;
	} catch (const char* e) {
		cerr << e << endl;
		return "";
	}
}

string Core::receive_with_key(string key, int fd)
{
	try {
		string response = ClientHandler::receive(fd);
		rapidjson::Document root;
		root.Parse<0>(response.c_str());
		if(root[key.c_str()].GetType())
			return root[key.c_str()].GetString();
		else
		{
			cerr << "Key not found" << endl;
			return "";
		}
	} catch (const char* e) {
		cerr << e << endl;
		return "";
	}
}

int Core::connect_to_file_server()
{
	int file_server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	int iSetOption = 1;
	setsockopt(file_server_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&iSetOption, sizeof(iSetOption));
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(FILE_SERVER_IP);
	serv_addr.sin_port = htons(FILE_SERVER_PORT);

	if(connect(file_server_fd, (struct sockaddr*)& serv_addr, sizeof(serv_addr)) == -1)
		throw string("I'm client and Could not connect to the file server");
	else
		cout << "I'm client and connected to file_server with fd " << file_server_fd << endl;

	return file_server_fd;
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

void Core::upload_photo(int file_server_fd, string local_path)
{
	char buf[1000];
	FILE* local_file = fopen(local_path.c_str(), "rb");
	int read_bytes = 0;
	cerr << "[Client] uploading photo to " << file_server_fd << endl;
	if(local_file == 0)
		throw Exception("File not found");
	cout << "[Core][upload_photo] before while" << endl;
	while((read_bytes = fread(buf,1,100,local_file)) > 0)
	{
		printf("read %d bytes\n",read_bytes);
		int written_bytes = write(file_server_fd, buf, read_bytes);
		printf("wrote %d bytes to server\n", written_bytes);
	}
}

void Core::post_photo(string title,string local_path, string hashtags, bool publicity)
{
	string CDN_path;
	Json json;
	map<string,string> params;
	params["title"] = title;
	//params["CDN_path"] = CDN_path;
	params["hashtags"] = hashtags;
	params["publicity"] = publicity ? "true" : "false";
	send_req("post_photo", params);

	cout << "waitint to receive user token from server" << endl;
	string token = receive_with_key("user_token");
	cout << "User received token:  " << token << endl;

	cout << "Client connecting to file server" << endl;
	params.clear();
	params["user_token"] = token;
	params["file_name"] = local_path;
	send_req("upload",params,file_server_fd);

	string result = receive_with_key("message", file_server_fd);
	cerr << "here" << endl;
	try {
		if(result == "accepted")
		{
			upload_photo(file_server_fd, local_path);
			cout << "[Client] uploading photo finished" << endl;
			CDN_path = simple_receive_data(file_server_fd);
			cout << "[Client] receive from file server CDN_path:  " << CDN_path << endl;
		}
		else
			throw Exception("Could not upload photo");
	} catch (Exception e) {
		send("quit",file_server_fd);
		send("quit");
		//close(file_server_fd);
		throw;
	}

	cout << "sending CDN_path to server" << endl;
	send(CDN_path);
	cout << "CDN_path sent to server. waiting for answer" << endl;
	simple_receive();
	cout << "Answer received and we are done" << endl;
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

bool Core::exist_in_cache(string file_name)
{
	if(FILE* file = fopen(("cache/"+file_name).c_str(), "r"))
	{
		fclose(file);
		return true;
	}
	else
		return false;

}

string Core::download_from_CDN(string file_name)
{
	cout << "=========== Downloading from CDN============" << endl;
	if(exist_in_cache(file_name))
		return "cache/"+file_name;
	else {
		map<string,string> params;
		params["file_name"] = file_name;
		send_req("download",params,file_server_fd);

		string result = receive_with_key("message",file_server_fd);

		if(result == "accepted")
		{
			char buf[1000];
			int numbytes = 0;
			int sum = 0;
			while((numbytes = read(file_server_fd, buf, 500)) > 0)
			{
				buf[numbytes < 500 ? numbytes : 500] = '\0';
				FILE* fp = fopen(("cache/" + file_name).c_str(),"ab");
				printf("read %d bytes from user socket\n",numbytes);
				int written_bytes = fwrite(buf,1,numbytes,fp);
				sum += written_bytes;
				printf("wrote %d bytes to disk\n",written_bytes);
				fclose(fp);
				if(numbytes < 500)
				{
					cout << "wrote less than 100 bytes, I think it's done" << endl;
					cout << "downloaded bytes:  " << sum << endl;
					break;
				}
			}
			return "cache/"+file_name;
		} else {
			cerr << "Failed to download file from CDN" << endl;
			return "";
		}
	}
}	

map<string,string> Core::get_post_info(int id)
{
	Json json;
	map<string,string> params;
	params["id"] = to_string(id);
	send_req("get_post_info",params);

	string data = receive_data();
	map<string, string> result = decode<map<string,string> >(data);
	
	cout << "===== changing CDN_path locally ====" << endl;
	cout << "default CDN_path:  " << result["photo_path"] << endl;
	result["photo_path"] = download_from_CDN(result["photo_path"]);
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
	send_req("get_comment",params);

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

bool Core::is_reportable(string username)
{
	map<string,string> params;
	params["username"] = username;
	send_req("is_reportable", params);

	string result = receive_data();
	if(result == "true")
		return true;
	else
		return false;
}
