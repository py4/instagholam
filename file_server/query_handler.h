#ifndef QUERY_HANDLER_H_
#define QUERY_HANDLER_H_

#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <Poco/Thread.h>
#include <vector>
#include "json.h"

class QueryHandler : public Poco::Runnable
{
public:
	QueryHandler();
	QueryHandler(int, std::string);
	virtual void run()
	{
		rapidjson::Document root;
		root.Parse<0>(query.c_str());
		std::string func = root["function"].GetString();
		std::string file_name = root["file_name"].GetString();

		if(func == "upload")
			std::string CDN_path = download_from_client(file_name);
	}

	std::string download_from_client(std::string);
private:
	int query_fd;
	std::string query;
};
#endif