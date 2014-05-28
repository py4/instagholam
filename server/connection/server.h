#ifndef SERVER_H_
#define SERVER_H_

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <string>
#include <unistd.h>
#include <Poco/Thread.h>
#include "connection_handler.h"
#define SERVER_PORT 3337
#define FILE_SERVER_PORT 3330
#define FILE_SERVER_IP "127.0.0.1"
#define MAX_CONNECTIONS 5
#define AUTH_TOKEN "abcdef"
#include <vector>
class Server
{
	friend class ConnectionHandler;
public:
	Server();
	void send(int,std::string);
	std::string receive(int);
private:
	int fd;
	std::vector<ConnectionHandler> connections;
	Poco::Thread threads[MAX_CONNECTIONS];
};

#endif