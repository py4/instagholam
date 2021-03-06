#ifndef FILE_SERVER_H_
#define FILE_SERVER_H_

#include "query_handler.h"
#define SERVER_PORT 3330
#define MAX_QUERIES 5
#define BUF_SIZE 4000000
#define MAX_CONNECTIONS 5

class FileServer
{
	friend class QueryHandler;
public:
	FileServer();
	void init();
	void handle_request(std::string, int);
	std::string download_from_client(std::string, int);
	static FileServer* instance();

private:
	int fd;
	//int client_fd;
	std::vector<QueryHandler> handlers;
	std::vector<Poco::Thread*> threads;
	std::vector<std::string> temp_tokens;
	std::string receive();
	std::string auth_token;

	bool authenticate(std::string);
	std::string generate_temp_token(std::string);
	bool authenticate_user(std::string);

};
#endif