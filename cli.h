#ifndef CLI_H_
#define CLI_H_

#include "db.h"
#include "exception.h"
#include <string>
#include "api.h"

class CLI
{

public:
	CLI();
	void start();
private:
	std::string command;
	map<string,string> params;
	void ensure_user();
	void ensure_no_user();
	Api* api;
};

#endif
