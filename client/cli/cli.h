#ifndef CLI_H_
#define CLI_H_

#include "exception.h"
#include <string>
#include "core.h"
#include <map>

class CLI
{

public:
	CLI();
	~CLI();
	void start();
private:
	std::string command;
	std::map<std::string,std::string> params;
	void ensure_user();
	void ensure_no_user();
	void show_post(int);
	void show_my_profile();
	void show_friend_profile(std::string);
	void show_users();
	void show_timelog();
	//Api* api;
};

#endif
