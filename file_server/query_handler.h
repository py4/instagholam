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
#include <iostream>
#include <map>
class FileServer;

class QueryHandler : public Poco::Runnable
{
public:
	QueryHandler();
	QueryHandler(FileServer*, int);
	virtual void run()
	{
		while(true)
		{
			std::cout << "[QueryHandler] waiting for new query" << std::endl;
			query  = receive();
			if(query == "quit")
			{
				close(query_fd);
				return;
			}

			std::cout << "file server query:  " << query << std::endl;
			rapidjson::Document root;
			root.Parse<0>(query.c_str());

			std::string func = root["function"].GetString();

			std::cout << "function is " << func << std::endl;
			if(func == "upload")
			{
				handle_upload(root);
			} else if(func == "generate_temp_token") {
				handle_generate_temp_token(root);
			}
		}
		std::cout << "[QueryHandler] closing query fd " << query_fd << std::endl;
		close(query_fd);
		//removing temp_token
	}

	std::string download_from_client(std::string);
//private:
	int query_fd;
	std::string query;
	void send(std::string);
	std::string receive();
	std::map < std::string, std::string> params;
	FileServer* server;
	void set_params(rapidjson::Document&);

	void handle_generate_temp_token(rapidjson::Document&);
	void handle_upload(rapidjson::Document&);
	void send_with_key(std::string data, std::string);
};
#endif