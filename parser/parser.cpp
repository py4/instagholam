#include "parser.h"
#include <sstream>
#include <iostream>
#include "exception.h"
using namespace std;

/* http://codereview.stackexchange.com/a/40158 */
void trim(string & str)
{
	const string whitespace = " \t\f\v\n\r";
	int start = str.find_first_not_of(whitespace);
	int end = str.find_last_not_of(whitespace);

	if(start == -1 or end == -1)
		str = "";
	else
	{
		str.erase(0,start);
		str.erase((end - start) + 1);
	}
}

string get_value_of_tag(string line)
{
	bool c = false;
	int first_index = 0, second_index = 0;
	for(int i = 0; i < line.length(); i++)
	{
		if(line[i] == '<')
		{
			c = true;
			first_index = i;
		}
		if(c)
		{
			if(line[i] == '>')
			{
				c = false;
				second_index = i;
				line.erase(line.begin()+first_index,line.begin()+second_index+1);
			}
		}	
	}

		return line;
}

void set_hash_params(map<string,string>& params, string keys[], int count, string line)
{
	stringstream in(line);
	string temp;
	for(int i = 0; getline(in,temp,' '); i++)
	{
		if(i >= count)
			throw BadInput();
		params[keys[i]] = temp;
	}
}

void set_params(map<string,string>& params, string command)
{
	params.clear();
	stringstream in(command);
	string temp;

	getline(in,temp,' ');
	params["command"] = temp;
	string keys[5];
	keys[0] = "command";

	if(temp == "register") {
		keys[1] = "username"; keys[2] = "password"; keys[3] = "name"; keys[4] = "avatar_path";
		set_hash_params(params,keys,5,command);
	}
	else if(temp == "login") {
		keys[1] = "username"; keys[2] = "password";
		set_hash_params(params,keys,3,command);
	}
	else if(temp == "post_photo") {
		keys[1] = "title"; keys[2] = "CDN_path"; keys[3] = "hashtags", keys[4] = "publicity";
		set_hash_params(params,keys,5,command);
	} else if(temp == "show_friend_profile" or temp == "remove_friend" or temp == "request_to_friend") {
		keys[1] = "username";
		set_hash_params(params,keys,2,command);
	} else if(temp == "disapprove_friend_request" or temp == "approve_friend_request" or temp == "like_post" or
		temp == "unlike_post") {
		keys[1] = "id";
		set_hash_params(params,keys,2,command);
	} else if(temp == "comment") {
		keys[1] = "id"; keys[2] = "content";
		set_hash_params(params,keys,3,command);
	}
}

bool is_tag(string line)
{
	if(line[0] == '<' and line[1] != '/' and *(line.end()-1) == '>')
		return true;
	return false;
}

bool is_closing_tag(string line)
{
	if(line[0] == '<' and line[1] == '/' and *(line.end()-1) == '>')
		return true;
	return false;
}

string get_tag_name(string line)
{
	string result = "";
	for(int i = 0; i < line.length(); i++)
	{
		if(line[i] == '<' or line[i] == '/' or line[i] == '>')
			continue;
		if(line[i] != ' ')
			result += line[i];
		else
			break;
	}
	return result;
	
}

map<string,string> get_attributes(string line)
{
	bool check = false;
	string temp;
	map <string,string> result;
	stringstream in;
	
	for(int i = 0; i < line.length(); i++)
	{
		if(!check)
		{
			if(line[i] == ' ')
			{
				check = true;
			}
		}
		else
			in << line[i];
	}

	string key,value;
	for(int i = 0; getline(in,temp,'='); i++)
	{
		if(i % 2 == 0)
			key = temp;
		else
		{
			temp.erase(temp.begin());
			temp.erase(temp.end()-2,temp.end());
			result[key] = temp;
		}
	}
	return result;
}

string get_depth_tabs(int depth)
{
	string result = "";
	for(int i = 0; i < depth; i++)
		result += '\t';
	return result;
}

vector <string> get_hashtags(string line)
{
	vector<string> result;
	istringstream str(line);
	string temp;
	int i = 0;
	while(getline(str,temp,'#'))
	{
		if(i != 0) //the first one...
			result.push_back(temp);
		i++;
	}
	return result;
}

int to_int(string line)
{
	stringstream stream(line);
	int result;
	stream >> result;
	return result;
}





