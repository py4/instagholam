#ifndef PARSER_H_
#define PARSER_H_

#include <map>
#include <string>
#include <vector>
using namespace std;

map <string,string> parse_book(string);
string get_value_of_tag(string);
string get_shelf_name(string);

bool is_tag(string);
bool is_closing_tag(string);
string get_tag_name(string);

string get_depth_tabs(int);
map <string,string> get_attributes(string);

string get_command_name(string);

map <string,string> get_sign_up_params(string);

void set_params(map<string,string>&,string);
void set_hash_params(map<string,string>&, string [], int, string);
void set_book_params(map<string,string>&,string);
void set_add_to_shelf_params(map<string,string>&, string);
std::vector <std::string> get_hashtags(std::string);
//void set_login_params(map<string,string>&,string);




void trim(string&);
#endif
